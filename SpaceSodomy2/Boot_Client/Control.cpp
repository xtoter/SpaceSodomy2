#include "Control.h"

void Control::get_files_list() {
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ServerIP, port);
	if (status != sf::Socket::Done){
		std::cout << "connection failed\n";
		get_files_list();
		return;
	}

	std::string data = "FileList";

	loading->step(25, "Requesting data");

	// TCP socket:
	if (socket.send(data.c_str(), 100) != sf::Socket::Done){
		std::cout << "failed to request data\n";
		get_files_list();
		return;
	}
	
	char* list = new char[100000];
	size_t received = 0;

	loading->step(50, "Receiving data");
	if (socket.receive(list, 100000, received) != sf::Socket::Done) {
		std::cout << "failed to receive data\n";
		get_files_list();
		return;
	}

	std::cout << "Received " << received << " bytes" << std::endl;

	for (int i = 0; i < received; i++)
		std::cout << list[i];

	std::stringstream files_list;

	files_list << std::string(list);

	std::string next, name;
	int size;

	while (!files_list.eof()) {
		if (next == "FILE") {
			files_list >> name >> next >> size >> next;
			files[name] = size;
		}
		files_list >> next;
	}

	delete[] list;
}

void Control::get_file(std::string path, std::string name) {
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ServerIP, port);
	if (status != sf::Socket::Done) {
		std::cout << "connection failed\n";
		get_file(path, name);
		return;
	}

	std::string request = "Get " + name + " 0 " + std::to_string(files[name]);

	// TCP socket:
	if (socket.send(request.c_str(), 100) != sf::Socket::Done) {
		std::cout << "failed to request data\n";
		get_file(path, name);
		return;
	}

	TCP_packet data;
	data.set_size(files[name] + 1);

	for (int i = 0; i < files[name]; i++) {
		sf::Packet packet;

		if (socket.receive(packet) != sf::Socket::Done) {
			std::cout << "failed to receive data\n";
			continue;
		}

		std::cout << "Received " << packet.getDataSize() << " bytes" << std::endl;
		data.set_packet(packet);
	}

	data.make_file(path);
}


Control::Control(std::string ServerIP_, int port_) {
	ServerIP = ServerIP_;
	port = port_;
	draw.create_window(600, 600, "Boot Client");
	draw.load_fonts("fonts.conf");
	draw.apply_camera(b2Vec2(0, 0), 1, 1.5 * b2_pi);
	loading = new Loading_Screen(&draw);
	loading->step(0, "Connecting to the server");
}