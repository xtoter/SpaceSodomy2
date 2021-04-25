#include "pch.h"
#include "TCP_packet.h"

namespace fs = std::experimental::filesystem;

int TCP_packet::file_size(std::string path) {
	std::ifstream file(path);
	int ans = file.rdbuf()->pubseekoff(0, file.end, file.in);
	return (ans + packet_size - 1) / packet_size;
}

void TCP_packet::make_packets(std::string path) {
	std::ifstream file(path);
	packets.clear();
	size = file_size(path) + 1;
	packets.resize(size);
	std::string cur;
	cur.resize(packet_size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; (j < packet_size && !file.eof()); j++) {
			cur[j] = file.get();
		}
		packets[i] << i << cur;
	}
}

void TCP_packet::make_file(std::string path_) {
	fs::path path = path_;
	fs::create_directories(path.parent_path());

	std::ofstream fout;
	fout.open(path);
	
	for (int i = 0; i < size; i++) {
		int num;
		std::string data;
		packets[i] >> num >> data;
		fout << data;
	}
	fout.close();
}

void TCP_packet::set_size(int size_) {
	size = size_;
	packets.resize(size);
}
void TCP_packet::set_packet(sf::Packet packet_) {
	int num;
	std::string data;
	packet_ >> num >> data;
	packet_ << num << data;
	packets[num] = packet_;
}

sf::Packet* TCP_packet::get_packet(int num) {
	return &packets[num];
}