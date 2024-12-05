#include <array>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "config.h"

void load_texture(const std::string path, sf::Texture* texture, sf::IntRect* rect, const std::string msg) {
	if (texture == nullptr) {
		throw std::runtime_error(msg);
	} else if (rect != nullptr) {
		if (!texture->loadFromFile(path, *rect)) {
			throw std::runtime_error(msg);
		}
	} else {
		if (!texture->loadFromFile(path)) {
			throw std::runtime_error(msg);
		}
	}
}

Config get_config() {
	int rows;
	int columns;
	int mines;
	std::string rows_str;
	std::string columns_str;
	std::string mines_str;
	std::ifstream stream("./files/config.cfg");
	getline(stream, columns_str);
	getline(stream, rows_str);
	getline(stream, mines_str);
	try {
		columns = stoi(columns_str);
		rows = stoi(rows_str);
		mines = stoi(mines_str);
	} catch (std::invalid_argument) {
		throw std::runtime_error("Could not parse config file.");
	}
	if (mines > (rows * columns)) {
		throw std::runtime_error("Config file invalid! Number of mines cannot exceed the number of tiles.");
	}
	sf::Texture hidden_tile;
	sf::Texture tile_revealed;
	sf::Texture flag;
	sf::Texture mine;
	sf::Texture	play;
	sf::Texture pause;
	sf::Texture debug;
	sf::Texture digits;
	sf::Texture face_happy;
	sf::Texture face_win;
	sf::Texture face_lose;
	sf::Texture leaderboard;
	sf::Texture number_1;
	sf::Texture number_2;
	sf::Texture number_3;
	sf::Texture number_4;
	sf::Texture number_5;
	sf::Texture number_6;
	sf::Texture number_7;
	sf::Texture number_8;
	load_texture("./files/images/tile_hidden.png", &hidden_tile, nullptr, "Could not load tile hidden texture!");
	load_texture("./files/images/tile_revealed.png", &tile_revealed, nullptr, "Could not load tile revealed texture!");
	load_texture("./files/images/flag.png", &flag, nullptr, "Could not load flag texture!");
	load_texture("./files/images/mine.png", &mine, nullptr, "Could not load mine texture!");
	load_texture("./files/images/play.png", &play, nullptr, "Could not load play texture!");
	load_texture("./files/images/pause.png", &pause, nullptr, "Could not load pause texture!");
	load_texture("./files/images/debug.png", &debug, nullptr, "Could not load debug texture!");
	load_texture("./files/images/digits.png", &digits, nullptr, "Could not load digits texture!");
	load_texture("./files/images/face_happy.png", &face_happy, nullptr, "Could not load happy face (reset button) texture!");
	load_texture("./files/images/face_win.png", &face_win, nullptr, "Could not load \"face win\" texture!");
	load_texture("./files/images/face_lose.png", &face_lose, nullptr, "Could not load \"face lose\" texture!");
	load_texture("./files/images/leaderboard.png", &leaderboard, nullptr, "Could not load leaderboard texture!");
	load_texture("./files/images/number_1.png", &number_1, nullptr, "Could not load number_1 texture!");
	load_texture("./files/images/number_2.png", &number_2, nullptr, "Could not load number_2 texture!");
	load_texture("./files/images/number_3.png", &number_3, nullptr, "Could not load number_3 texture!");
	load_texture("./files/images/number_4.png", &number_4, nullptr, "Could not load number_4 texture!");
	load_texture("./files/images/number_5.png", &number_5, nullptr, "Could not load number_5 texture!");
	load_texture("./files/images/number_6.png", &number_6, nullptr, "Could not load number_6 texture!");
	load_texture("./files/images/number_7.png", &number_7, nullptr, "Could not load number_7 texture!");
	load_texture("./files/images/number_8.png", &number_8, nullptr, "Could not load number_8 texture!");
	return Config {
		.rows = rows,
		.columns = columns,
		.mines = mines,
		.textures = {
			.hidden_tile = hidden_tile,
			.tile_revealed = tile_revealed,
			.flag = flag,
			.mine = mine,
			.play =	play,
			.pause = pause,
			.debug = debug,
			.digits = digits,
			.face_happy = face_happy,
			.face_win = face_win,
			.face_lose = face_lose,
			.leaderboard = leaderboard,
			.number_1 = number_1,
			.number_2 = number_2,
			.number_3 = number_3,
			.number_4 = number_4,
			.number_5 = number_5,
			.number_6 = number_6,
			.number_7 = number_7,
			.number_8 = number_8,
		}
	};
}

void display_config(Config& cfg) {
	std::cout << "Config {" << '\n';
	std::cout << "\trows = " << cfg.rows << ',' << '\n';
	std::cout << "\tcolumns = " << cfg.columns << ',' << '\n';
	std::cout << "\ttextures = {}" << ',' << '\n';
	std::cout << "\tmines = " << cfg.mines << ",\n}\n";
}
