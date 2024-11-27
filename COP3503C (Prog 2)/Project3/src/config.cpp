#include <iostream>
#include <fstream>
#include <stdexcept>
#include "config.h"

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
	if (!hidden_tile.loadFromFile("./files/images/tile_hidden.png")) {
		throw std::runtime_error("Could not load tile_hidden texture!");
	}
	if (!tile_revealed.loadFromFile("./files/images/tile_revealed.png")) {
		throw std::runtime_error("Could not load tile_revealed texture!");
	}
	if (!flag.loadFromFile("./files/images/flag.png")) {
		throw std::runtime_error("Could not load flag texture!");
	}
	if (!mine.loadFromFile("./files/images/mine.png")) {
		throw std::runtime_error("Could not load mine texture!");
	}
	if (!play.loadFromFile("./files/images/play.png")) {
		throw std::runtime_error("Could not load play texture!");
	}
	if (!pause.loadFromFile("./files/images/pause.png")) {
		throw std::runtime_error("Could not load pause texture!");
	}
	if (!debug.loadFromFile("./files/images/debug.png")) {
		throw std::runtime_error("Could not load debug texture!");
	}
	if (!digits.loadFromFile("./files/images/digits.png")) {
		throw std::runtime_error("Could not load digits texture!");
	}
	if (!face_happy.loadFromFile("./files/images/face_happy.png")) {
		throw std::runtime_error("Could not load face_happy texture!");
	}
	if (!face_win.loadFromFile("./files/images/face_win.png")) {
		throw std::runtime_error("Could not load face_win texture!");
	}
	if (!face_lose.loadFromFile("./files/images/face_lose.png")) {
		throw std::runtime_error("Could not load face_lose texture!");
	}
	if (!leaderboard.loadFromFile("./files/images/leaderboard.png")) {
		throw std::runtime_error("Could not load leaderboard texture!");
	}
	if (!number_1.loadFromFile("./files/images/number_1.png")) {
		throw std::runtime_error("Could not load number_1 texture!");
	}
	if (!number_2.loadFromFile("./files/images/number_2.png")) {
		throw std::runtime_error("Could not load number_2 texture!");
	}
	if (!number_3.loadFromFile("./files/images/number_3.png")) {
		throw std::runtime_error("Could not load number_3 texture!");
	}
	if (!number_4.loadFromFile("./files/images/number_4.png")) {
		throw std::runtime_error("Could not load number_4 texture!");
	}
	if (!number_5.loadFromFile("./files/images/number_5.png")) {
		throw std::runtime_error("Could not load number_5 texture!");
	}
	if (!number_6.loadFromFile("./files/images/number_6.png")) {
		throw std::runtime_error("Could not load number_6 texture!");
	}
	if (!number_7.loadFromFile("./files/images/number_7.png")) {
		throw std::runtime_error("Could not load number_7 texture!");
	}
	if (!number_8.loadFromFile("./files/images/number_8.png")) {
		throw std::runtime_error("Could not load number_8 texture!");
	}
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
