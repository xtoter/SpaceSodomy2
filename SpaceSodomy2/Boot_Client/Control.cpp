#include "Control.h"

Control::Control() {
	draw.create_window(600, 600, "Boot Client");
	draw.load_fonts("fonts.conf");
	draw.apply_camera(b2Vec2(0, 0), 1, 1.5 * b2_pi);
	Loading_Screen loading(&draw);
}