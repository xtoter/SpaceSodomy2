#include "Control.h"

void Control::get_replays() {
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ServerIP, port);
	if (status != sf::Socket::Done){
		std::cout << "connection failed\n";
		return;
	}

	char data[100] = {'r', 'e', 'p', 'l', 'a', 'y', 's'};

	loading->step(25, "Requesting data");

	// TCP socket:
	if (socket.send(data, 100) != sf::Socket::Done){
		std::cout << "failed to request data\n";
		return;
	}
	
	char* big_data = new char[500000000];
	size_t received = 0;

	loading->step(50, "Receiving data");
	if (socket.receive(big_data, 500000000, received) != sf::Socket::Done) {
		std::cout << "failed to receive data\n";
		return;
	}

	std::cout << "Received " << received << " bytes" << std::endl;

	delete big_data;
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