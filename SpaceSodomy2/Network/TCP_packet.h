#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <AuxLib/AuxLib.h>
#include <experimental/filesystem>
#include <stdio.h>
#include <SFML/Network.hpp>
#include <fcntl.h>
#include <io.h> 
class TCP_packet {
private:
	int size = 0;
	std::vector <sf::Packet> packets;
public:
	static const int packet_size = 1000;
	static int file_size(std::string path);

	void make_packets(std::string path);
	void make_file(std::string path_);

	void set_size(int size_);
	void set_packet(sf::Packet);

	sf::Packet* get_packet(int num);
};

