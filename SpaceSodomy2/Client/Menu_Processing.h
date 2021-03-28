#pragma once
#include<Menu/Menu.h>
#include<AuxLib/AuxLib.h>
#include<string>

class Menu_Processing {
private:
	Menu main_menu; // main menu object
	Menu config_menu; // config menu object
	Menu keys_menu; // keys menu object
	Menu settings_menu; // settings menu object
	Menu sound_menu; // sound menu object
	Menu gun_menu; // gun menu object
	std::map <std::string, Menu> guns; // guns

	std::vector<Menu*> menus;
	aux::Keyboard* keyboard;
	b2Vec2* mouse_pos;
	int current_id = 1;
	bool* reload;
	std::queue<int> events; // menu events
	std::map<int, std::string> text_fields_strings; // texts from text fields
	std::map<int, int> sliders_vals; // vals from sliders
	std::map<std::string, int> name_to_id;
	std::map<int, std::string> id_to_name;
	std::vector<std::vector<std::string*>> keys_menu_vec;
	void save_config(std::string path, std::string address_, int port_, int id_, std::string name_);
	void load_config(std::string path, std::string* address_, std::string* port_,
		std::string* id_, std::string* name_);
	void save_keys(std::string path, std::vector<std::vector<std::string*>> keys);
	void load_keys(std::string path, std::vector<std::vector<std::string*>>* keys, Menu* menu,
		b2Vec2 pos, float name_indent, b2Vec2 indent, int character_size);
	void load_sound(std::string path);
	void save_sound(std::string path);
	void init_menu(std::string path_, Menu* object);
	void init_gun(std::string, int damage, float recharge, int stamina_consumption, float projectile_mass,
		float projectile_radius, int projectile_vel, Menu* gun);
	void init_gun_menu(std::string path, std::string path_to_guns_description);
	Draw* draw;
	bool disactivated = 0;

	int* music_volume;
	int* sound_volume;
public:
	Menu_Processing();
	bool active = 1;
	void init(Draw* draw, b2Vec2* mouse_pos_,
		aux::Keyboard* keyboard_, bool* reload_,
		int* sound_volume_, int* music_volume_);
	void step();
};


