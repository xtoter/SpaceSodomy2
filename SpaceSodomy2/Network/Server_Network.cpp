#include <pch.h>
#include "Server_Network.h"

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
	socket.receive(received, sender, port);
	if (received.getDataSize())
	{
		// Applying sender info
		addresses.insert(sender);
		ports[sender] = port;
		IPconvert[sender.toString()] = sender;

		// Applying received info
		std::string message_;
		received >> message_;
		message_ = sender.toString() + " " + message_; // adding IP address to message
		messages.push_back(message_);
	}
}

void Server_Network::send(std::string message) {
	if (replay_path != "") {
		if (!fout.is_open())
			fout.open(replay_path);
		fout << message << "\n";
	}
	sf::Packet to_send;
	to_send << message;
	//send message for all users
	for (auto addr : addresses) {
		socket.send(to_send, addr, ports[addr]);
	}
}