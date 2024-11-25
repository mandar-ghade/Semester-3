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
	return Config {
		.rows = rows,
		.columns = columns,
		.mines = mines
	};
}

void display_config(Config& cfg) {
	std::cout << "Config {" << '\n';
	std::cout << "\trows = " << cfg.rows << ',' << '\n';
	std::cout << "\tcolumns = " << cfg.columns << ',' << '\n';
	std::cout << "\tmines = " << cfg.mines << ",\n}\n";
}
