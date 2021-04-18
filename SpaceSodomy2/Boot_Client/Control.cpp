#include "Control.h"

void Control::get_replays() {
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ServerIP, port);
	if (status != sf::Socket::Done){
		std::cout << "connection failed";
		return;
	}

	char data[100] = {'r', 'e', 'p', 'l', 'a', 'y', 's'};

	// TCP socket:
	if (socket.send(data, 100) != sf::Socket::Done){
		std::cout << "failed to request data";
		return;
	}
}

Control::Control(std::string ServerIP_, int port_) {
	ServerIP = ServerIP_;
	port = port_;
	draw.create_window(600, 600, "Boot Client");
	draw.load_fonts("fonts.conf");
	draw.apply_camera(b2Vec2(0, 0), 1, 1.5 * b2_pi);
	Loading_Screen loading(&draw);
}