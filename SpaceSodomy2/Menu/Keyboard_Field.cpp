#include "pch.h"
#include "Keyboard_Field.h"

Keyboard_Field::Keyboard_Field() {
	set_use_picture_scale(0);
	text.setString(L"None");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(10);
}

// Get methods
std::string Keyboard_Field::get_text() {
	return text.getString();
}
sf::Font Keyboard_Field::get_font() {
	return *text.getFont();
}
sf::Color Keyboard_Field::get_text_color() {
	return text.getFillColor();
}
unsigned int Keyboard_Field::get_text_character_pixels_size() {
	return text.getCharacterSize();
}
b2Vec2 Keyboard_Field::get_indent() {
	return indent;
}
bool Keyboard_Field::get_keyboard_active() {
	return keyboard_active;
}

// Set methods
void Keyboard_Field::set_text(std::string text_) {
	text.setString(text_);
}
void Keyboard_Field::set_font(sf::Font font_) {
	font_setted = 1;
	text.setFont(font_);
	height = aux::get_text_max_height(text);
}
void Keyboard_Field::set_text_color(sf::Color color_) {
	text.setFillColor(color_);
}
void Keyboard_Field::set_text_character_pixel_size(unsigned int size_) {
	text.setCharacterSize(size_);
}
void Keyboard_Field::set_indent(b2Vec2 indent_) {
	indent = indent_;
}
void Keyboard_Field::set_keyboard_active(bool keyboard_active_) {
	keyboard_active = keyboard_active_;
}
void Keyboard_Field::set_align(int align_) {
	align = align_;
}

void Keyboard_Field::step() {
	primitive_step();
	if (!font_setted) { // if font isn't setted -> set standart font
		font_setted = 1;
		text.setFont(*(get_draw()->get_font("font")));
		height = height = aux::get_text_max_height(text);
	}
	// Key entering
	if (keyboard_active) {
		for (int i = 0; i < get_keyboard()->state_current.size(); i++) {
			if (!get_keyboard()->state_prev[i] && get_keyboard()->state_current[i]) {
				text.setString(get_keyboard()->names[i]);
				keyboard_active = 0;
				break;
			}
		}
	}
	// Set background params
	text.setScale({ (float)get_screen_mode(), (float)get_screen_mode() });
	set_scale(b2Vec2(text.getLocalBounds().width, text.getLocalBounds().height));
	set_scale(get_scale() + indent);
	set_color(sf::Color(40, 40, 40, 255));
	switch (align)
	{
	case 1:
		set_cur_pos(b2Vec2(get_pos().x + get_screen_mode() * text.getLocalBounds().width / 2, get_pos().y));
		break;
	case 2:
		set_cur_pos(b2Vec2(get_pos().x - get_screen_mode() * text.getLocalBounds().width / 2, get_pos().y));
		break;
	default:
		set_cur_pos(get_pos());
		break;
	}
	if (keyboard_active)
		get_draw()->stroke_rect(get_cur_pos() + get_screen_mode() * b2Vec2(indent.x / 2.0, indent.y / 2.0),
			 get_screen_mode() * (get_scale() + indent), sf::Color::White);
	//std::cout << "Text: " << *get_clicked() << " " << get_active() << " " << keyboard_active << " " << text.getString().toAnsiString() << "\n";
	text.setPosition((aux::to_Vector2f(get_cur_pos()) - 
		sf::Vector2f(get_screen_mode() * text.getLocalBounds().width / 2.0, get_screen_mode() * text.getLocalBounds().height / 2.0)));
	get_draw()->display_text(&text);
}