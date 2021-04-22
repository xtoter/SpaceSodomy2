#pragma once
#include <AuxLib/AuxLib.h>
#include <Draw/Draw.h>
#include <Audio/Audio.h>
#include <Menu/Loading_Screen.h>
#include <SFML/Network.hpp>
class Control {
private:
	// Contains window 7 other drawing stuff
	Draw draw;
	std::string ServerIP;
	int port;
	Loading_Screen* loading = nullptr;
public:
	Control(std::string ServerIP_, int port_);

	void get_replays();
};

