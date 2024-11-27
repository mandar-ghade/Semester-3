#pragma once
#include <SFML/Graphics.hpp>
struct Textures {
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
};

struct Config {
	int rows;
	int columns;
	int mines;
	Textures textures;
};

Config get_config();
void display_config(Config& cfg);
