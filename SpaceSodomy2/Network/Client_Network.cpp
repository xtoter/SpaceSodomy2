#include "pch.h"
#include "Client_Network.h"
#include <thread> 

//basic constructors
Client_Network::Client_Network() {
	socket.setBlocking(1);
}

Client_Network::Client_Network(std::string serverIP_, int port_, int id_, std::string name_, int token_) {
	port = port_;
	serverIP = serverIP_;
	id = id_;
	name = name_;
	socket.setBlocking(1);
	socket_receiving.setBlocking(1);
	token = token_;
}

//Set modules
void Client_Network::set_port(int port_) {
	port = port_;
}

void Client_Network::set_server(std::string serverIP_) {
	serverIP = serverIP_;
}

void Client_Network::set_id(int id_) {
	id = id_;
}

void Client_Network::set_name(std::string name_) {
	name = name_;
}

void Client_Network::set_token(int token_) {
	token = token_;
}

//Get modules
int Client_Network::get_port() {
	return port;
}

std::string Client_Network::get_serverIP() {
	return serverIP;
}

int Client_Network::get_id() {
	return id;
}

std::string Client_Network::get_name() {
	return name;
}
int Client_Network::get_token() {
	return token;
}

void Client_Network::send(std::string data) {
	// Client message constructor
	data = std::to_string(id) + " " +
		std::to_string(aux::get_milli_count()) + " " +
		name + " " + std::to_string(token) + " " +
		data;
	// Sending
	auto func = [](sf::UdpSocket* socket, std::string data,
		std::string serverIP, int port) {
		sf::Packet to_send;
		to_send << data;
		socket->send(to_send, serverIP, port);
	};

	std::thread thread(func, &socket, data, serverIP, port);
	thread.detach();
}

void Client_Network::receive() {
	//Cycle used to keep network stack empty
	for (int i = 0; i < 2; i++) {
		// buffer saves only last message
		auto func = [](sf::UdpSocket* socket, std::string* data, int* x) {
			*x += 1;
			sf::Packet packet;
			sf::IpAddress sender;
			unsigned short port_ = 0;
			socket->receive(packet, sender, port_);
			packet >> *data;
			*x -= 1;
		};
		std::thread thread(func, &socket, &received_data, &x);
		thread.detach();
	}	
	std::cout << x << "\n";
}

std::string Client_Network::get_message() {
	return received_data;
}