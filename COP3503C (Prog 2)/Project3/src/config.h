#pragma once
struct Config {
	int rows;
	int columns;
	int mines;
};

Config get_config();
void display_config(Config& cfg);
