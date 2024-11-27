#pragma once
#include <iostream>
#include <random>
#include "config.h"
#include "tile.h"

class Board {
private:
	const size_t rows;
	const size_t columns;
	const size_t mine_count;
	Config& cfg;
	std::vector<std::vector<Tile*>> tiles;
	std::vector<Tile*> mines;
	void generate_board(); 
	void assign_neighboring_tiles();
	void plant_mines(); 
public:
	Board(Config& cfg): 
		rows(cfg.rows),
		columns(cfg.columns),
		mine_count(cfg.mines),
		cfg(cfg)
	{
		generate_board();
	}
	void do_left_click(sf::Event::MouseButtonEvent& mouse); 
	void reset(); 
	void draw_sprites(sf::RenderWindow& window); 
	void print_as_str(); 
	~Board() {
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				delete (*col);
			}
		}
	}
};
