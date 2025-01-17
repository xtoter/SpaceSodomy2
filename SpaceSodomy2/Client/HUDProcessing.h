#pragma once
#include<Menu/Bar.h>
#include<Client/GameClient.h>
#include<AuxLib/AuxLib.h>
#include<Network/ClientNetwork.h>

class HUDProcessing {
private:
	Bar HP_bar, stamina_bar, energy_bar;
	Constant_Text time_to_respawn, press_r_to_respawn,
		ping, ping_text, fps, fps_text;
	Menu_Object bonus, left_module, right_module, interface_image, gun_image;
	Text_Field bonus_tip, left_module_tip, right_module_tip;

	int table_use_windows_cords;
	b2Vec2 table_pos;
	float table_character_size;
	float table_name_indent;
	b2Vec2 table_indent;

	GameClient* game;
	ClientNetwork* player_network;

	Draw* draw;
	b2Vec2* mouse_pos;
	aux::Keyboard* keyboard;

	std::string bonus_button_name, left_module_button_name, right_module_button_name, respawn_button_name;

	void get_buttons_names(std::string path);
	void apply_bar(Bar* bar, std::stringstream* config);
	void table_step();

	int HP_bar_max_val;
	int stamina_bar_max_val;
	float HP_bar_val;
	float stamina_bar_val;
	int energy_bar_max_val;
	float energy_bar_val;
	float text_mod = 1;
	std::queue<int>* frame_marks;

	std::vector<b2Vec2> get_vertices(float cur_pos, b2Vec2 center, b2Vec2 scale);
public:
	float interface_scale = 3;

	HUDProcessing();
	HUDProcessing(Draw* draw_, b2Vec2* mouse_pos_, aux::Keyboard* keyboard_, GameClient* game_,
		ClientNetwork* player_network_, std::queue<int>* frame_marks_);

	void step();
};

