#pragma once
#include <AuxLib/AuxLib.h>
#include <Draw/Draw.h>
#include <Audio/Audio.h>
#include <Menu/Loading_Screen.h>
#include <SFML/Network.hpp>
#include <Network/TCP_packet.h>
class Control {
private:
	// Contains window 7 other drawing stuff
	Draw draw;
	std::string ServerIP;
	int port;
	Loading_Screen* loading = nullptr;
	std::map<std::string, int> files;
public:
	Control(std::string ServerIP_, int port_);

	void get_files_list();
	void get_file(std::string path, std::string name);
};

