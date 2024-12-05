#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Textures {
	const sf::Texture hidden_tile;
	const sf::Texture tile_revealed;
	const sf::Texture flag;
	const sf::Texture mine;
	const sf::Texture play;
	const sf::Texture pause;
	const sf::Texture debug;
	const sf::Texture digits;
	const sf::Texture face_happy;
	const sf::Texture face_win;
	const sf::Texture face_lose;
	const sf::Texture leaderboard;
	const sf::Texture number_1;
	const sf::Texture number_2;
	const sf::Texture number_3;
	const sf::Texture number_4;
	const sf::Texture number_5;
	const sf::Texture number_6;
	const sf::Texture number_7;
	const sf::Texture number_8;
};

struct Config {
	const int rows;
	const int columns;
	const int mines;
	const Textures textures;
};

void load_texture(const std::string path, sf::Texture* texture, sf::IntRect* rect, const std::string msg);
Config get_config();
void display_config(Config& cfg);
