#pragma once
#include "Button.h"
#include <vector>
#include <queue>

class Menu {
private:
	std::vector<Button*> buttons;
	Draw* draw;
	std::queue<int>* events;
	bool active = 0;
public:
	Menu();
	Menu(Draw* draw_);

	//Set methods
	void set_draw(Draw* draw_);
	void set_active(bool active_);
	void set_events(std::queue<int>* events_);
	
	//Get methods
	Draw* get_draw();
	bool get_active();
	std::queue<int>* get_events();

	void add_button(int id, std::string texture_name, float pos_x, float pos_y, float scale_x, float scale_y, sf::Color color, b2Vec2* mouse_pos);
	void step();
};