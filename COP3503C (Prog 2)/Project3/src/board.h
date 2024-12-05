#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "config.h"
#include "tile.h"

class Board {
private:
	Config* cfg;
	std::vector<std::vector<Tile>> tiles;
	void generate_board(); 
	void assign_neighboring_tiles();
	void plant_mines(); 
public:
	Board(Config* cfg): 
		cfg(cfg)
	{
		generate_board();
	}
	Tile* get_clicked_tile(const sf::Vector2i& mouse);
	void reset(); 
	void draw_sprites(sf::RenderWindow* window, bool debug_mode, bool paused); 
	void print_as_str(); 
	int count_hidden_tiles();
	int count_flagged_tiles();
	std::vector<Tile*> get_mines();
};
