#include "pch.h"
#include "Server_Network.h"

namespace fs = std::experimental::filesystem;

//basic constuctors
Server_Network::Server_Network() {
	socket.bind(8001);
	socket.setBlocking(0);
}

Server_Network::Server_Network(int port_) {
	socket.bind(port_);
	socket.setBlocking(0);
}

//Set methods
void Server_Network::set_port(int port_) {
	socket.bind(port_);
	socket.setBlocking(0);
}

void Server_Network::set_replay_path(std::string replay_path_) {
	replay_path = replay_path_;
}

//Get methods
std::deque<std::string> Server_Network::get_messages() {
	return messages;
}

std::string Server_Network::get_last_message() {
	if (messages.empty())
		return "";
	return messages.back();
}

//Delete methods
void Server_Network::del_last_message() {
	if (!messages.empty())
		messages.pop_back();
}

void Server_Network::clear_messages() {
	messages.clear();
}

void Server_Network::del_address(std::string address_) {
	addresses.erase(IPconvert[address_]);
}

void Server_Network::receive() {
	// Receiving
	socket.receive(buffer, sizeof(buffer), received, sender, port);
	if (received)
	{
		// Applying sender info
		addresses.insert(sender);
		ports[sender] = port;
		IPconvert[sender.toString()] = sender;

		// Applying received info
		std::string message_ = sender.toString() + " " + std::string(buffer); // adding IP address to message
		messages.push_back(message_);
		received = 0;
	}
}

void Server_Network::send(std::string message) {
	if (replay_path != "") {
		if (!fout.is_open())
			fout.open(replay_path);
		fout << message << "\n";
	}
	//send message for all users
	for (auto addr : addresses) {
		socket.send(message.c_str(), message.size() + 1, addr, ports[addr]);
	}
}

void Server_Network::boot_response() {
	auto response = []() {
		sf::TcpListener listener;
		if (listener.listen(8002) != sf::Socket::Done) {
			std::cout << "boot listener failed\n";
			return;
		}

		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done) {
			std::cout << "boot client failed\n";
			return;
		}
		char data[100];
		std::size_t received;

		if (client.receive(data, 100, received) != sf::Socket::Done) {
			std::cout << "client receive failed\n";
			return;
		}
		std::cout << "Received " << received << " bytes" << std::endl;

		std::map<std::string, std::string> files;

		for (auto file_path : fs::directory_iterator("replays")) {
			files[file_path.path().filename().u8string()] = file_path.path().u8string();
		}

		std::string request(data);

		std::stringstream request_stream;

		request_stream << request;
		request_stream >> request;

		if (request == "FileList") {
			std::string answer = "";
			for (auto file_path : fs::directory_iterator("replays")) {
				std::string filename = file_path.path().filename().u8string();
				answer += "FILE " + filename + " # " + std::to_string(TCP_packet::file_size(file_path.path().u8string())) +
					" packets\n";
			}
			answer += "END\n";
			if (client.send(answer.c_str(), answer.length()) != sf::Socket::Done) {
				std::cout << "sending failed";
				return;
			}
		}

		if (request == "Get") {
			std::string name;

			int beg, end;

			request_stream >> name >> beg >> end;

			if (files[name] == "")
				return;

			//fs::path p = files[name];

			//p.replace_extension(".txt");

			TCP_packet packet;
			packet.make_packets(files[name]);

			for (int i = beg; i < end; i++) {
				if (client.send(*packet.get_packet(i)) != sf::Socket::Done) {
					std::cout << "sending failed";
					return;
				}
			}
		}
	};
	std::thread thread(response);

	thread.detach();
}