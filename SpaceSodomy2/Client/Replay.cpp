#include "Replay.h"

Replay::Replay() {}

Replay::Replay(std::string path) {
	set_replay_path(path);
}

void Replay::set_replay_path(std::string path) {
	frames.clear();
	std::ofstream fail(path, std::ios::app);
	fail << '\0';
	fail.close();
	std::ifstream file(path, std::ios::binary);
	auto get_msg = [](std::ifstream& file) {
		std::string val;
		val += "Mmaps/rocks.lvl";
		unsigned char a;
		while ((a = file.get(), val.push_back(a)), a != '\0') {
			if (val.size() > 2000) {
				return std::string("");
			}
			if (val.size() >= 16) {
				if (val.substr(val.size() - 16) == "\nMmaps/rocks.lvl") {
					for (int i = 0; i <= 15; i++) {
						val.pop_back();
					}
					return val;
				}
			}
		}
		return val;
	};
	while (!file.eof()) {
		frames.push_back(get_msg(file));
	}
	replay_frame.set_max(frames.size() - 2);
}

void Replay::increase_speed() {
	if (replay_frame.get_change_vel() > -b2_epsilon && replay_frame.get_change_vel() < b2_epsilon) {
		replay_frame.set_change_vel(0.5);
		return;
	}
	if (replay_frame.get_change_vel() > b2_epsilon) {
		replay_frame.set_change_vel(replay_frame.get_change_vel() * 2);
		if (replay_frame.get_change_vel() > 64.0) {
			replay_frame.set_change_vel(64.0);
		}
		return;
	}
	if (replay_frame.get_change_vel() < -b2_epsilon) {
		if (replay_frame.get_change_vel() > -0.5 - b2_epsilon)
			replay_frame.set_change_vel(0);
		else
			replay_frame.set_change_vel(replay_frame.get_change_vel() / 2);
	}
}

void Replay::decrease_speed() {
	if (replay_frame.get_change_vel() > -b2_epsilon && replay_frame.get_change_vel() < b2_epsilon) {
		replay_frame.set_change_vel(-0.5);
		return;
	}
	if (replay_frame.get_change_vel() < -b2_epsilon) {
		replay_frame.set_change_vel(replay_frame.get_change_vel() * 2);
		if (replay_frame.get_change_vel() < -64.0) {
			replay_frame.set_change_vel(-64.0);
		}
		return;
	}
	if (replay_frame.get_change_vel() > b2_epsilon) {
		if (replay_frame.get_change_vel() < 0.5 + b2_epsilon)
			replay_frame.set_change_vel(0);
		else
			replay_frame.set_change_vel(replay_frame.get_change_vel() / 2);
	}
}

void Replay::set_replay_active(bool val) {
	replay_active = val;
}

std::string Replay::get_cur_frame() {
	return (frames[replay_frame.get()]);
}

Counter* Replay::get_replay_frame() {
	return &replay_frame;
}

bool Replay::get_replay_active() {
	return replay_active;
}