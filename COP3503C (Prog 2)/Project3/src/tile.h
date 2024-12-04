#pragma once
#include "config.h"
#include <iostream>
#include <vector>

class Tile {
private:
	int adjacent_mines = 0;
	bool contains_mine = false;
	bool is_hidden = true;
	bool flagged = false;
	Config* cfg;
	sf::RectangleShape background;
	sf::Sprite sprite;
	sf::RectangleShape top_layer;
public:
	const int x;
	const int y;
	struct AdjacentTiles {
		Tile* adjacent[8];
	};
	AdjacentTiles tiles;
	Tile(int x, int y, int total_rows, Config* cfg):
		adjacent_mines(0),
		cfg(cfg),
		x(x), y(y),
		tiles( AdjacentTiles { .adjacent = {} } )
	{
		background.setSize(sf::Vector2f(32, 32));
		background.setTexture(&this->cfg->textures.hidden_tile);
		background.setPosition(
			sf::Vector2f((float)x * 32, ((float)total_rows - (float)y - 1) * 32)
		);
		sprite.setTexture(cfg->textures.hidden_tile);
		sprite.setPosition(
			sf::Vector2f((float)x * 32, ((float)total_rows - (float)y - 1) * 32)
		);
		top_layer.setSize(sf::Vector2f(32, 32));
		top_layer.setPosition(
			sf::Vector2f((float)x * 32, ((float)total_rows - (float)y - 1) * 32)
		);
		top_layer.setTexture(&this->cfg->textures.flag);
	};
	sf::RectangleShape& get_top_layer(); 
	sf::RectangleShape& get_background(); 
	sf::Sprite& get_sprite(); 
	std::string as_str() const; 
	void plant_mine(); 
	void set_matching_texture(); 
	void incr_adj_mine_counts() const; 
	void reveal_adjacent_tiles();
	void reveal_tile(); 
	bool has_mine() const;
	bool has_detonated() const; 
	bool get_is_hidden() const; 
	int get_adjacent_mines() const; 
	bool get_is_flagged() const; 
	void set_flag_state(bool is_flagged); 
	void assign_neighboring_tiles(std::vector<std::vector<Tile>>& board); 
	AdjacentTiles get_neighbors() const; 
};

