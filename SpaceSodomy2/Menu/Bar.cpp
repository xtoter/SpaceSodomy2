#include "pch.h"
#include "Bar.h"

Bar::Bar() {
	set_image_active(0);
	set_use_picture_scale(0);
}

void Bar::step() {
	text.set_pos(get_pos());
	text.set_text(std::to_string(value));
	text.set_color(text_color);
	text.set_text_character_pixel_size(character_size);
	text.set_draw(get_draw());
	text.set_mouse_pos(get_mouse_pos());

	primitive_step();
	std::cout << get_pos().x << " " << get_pos().y << " " << get_scale().x << " " << get_scale().y << "\n";
	get_draw()->fill_rect(get_pos(), get_scale(), back_color);
	get_draw()->fill_rect(get_pos() - b2Vec2(get_scale().x * (max_value - value) / max_value / 2 , 0),
		get_scale() - b2Vec2(get_scale().x * (max_value - value) / max_value, 0), front_color);
	text.step();
}