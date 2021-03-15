#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <AuxLib/AuxLib.h>
#include <Draw/Draw.h>
#include <string>
#include <map>
#include <fstream>

class Audio {
private:
	std::map<std::string, sf::Sound*> sounds;
	std::vector<sf::Sound*> activeSounds;
	void load_sound(std::string name, std::string path_to_sound);
	Draw* draw;
public:
	Audio();

	void set_draw(Draw* draw_);
	
	Draw* get_draw();

	void load_sounds(std::string path = "sounds.conf");

	void play(std::string name, b2Vec2 pos, double z, double volume);
	void play(std::string name, b2Vec2 pos, double volume);
};