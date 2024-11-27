#pragma once
#include "config.h"
#include <iostream>
#include <vector>

enum TILE_STATE {
	HIDDEN,
	REVEALED,
};

struct Mine {
	int x;
	int y;
	bool has_detonated;
	Mine(int x, int y): x(x), y(y), has_detonated(false) {};
};


class Tile {
private:
	Mine* mine = nullptr;
	int adjacent_mines = 0;
	TILE_STATE current_state;
	bool flagged = false;
	Config& cfg;
	sf::Sprite sprite;
public:
	const int x;
	const int y;
	struct AdjacentTiles {
		Tile* adjacent[8];
	};
	AdjacentTiles tiles;
	Tile(int x, int y, int total_rows, Config& cfg):
		mine(nullptr),
		adjacent_mines(0),
		current_state(TILE_STATE::HIDDEN),
		cfg(cfg),
		x(x), y(y),
		tiles( AdjacentTiles { .adjacent = {} } )
	{
		sprite.setTexture(cfg.textures.hidden_tile);
		sprite.setPosition(
			sf::Vector2f((float)x * 32, ((float)total_rows - (float)y - 1) * 32)
		);
	};

	sf::Sprite& get_sprite(); 
	std::string as_str() const; 
	void plant_mine(); 
	void set_matching_texture(); 
	void incr_adj_mine_counts() const; 
	void reveal_tile(); 
	bool has_mine() const;
	bool has_detonated() const; 
	TILE_STATE get_state() const; 
	int get_adjacent_mines() const; 
	bool get_is_flagged() const; 
	void set_flag_state(bool is_flagged); 
	void detonate_mine(); 
	void assign_neighboring_tiles(const std::vector<std::vector<Tile*>>& board); 
	AdjacentTiles get_neighbors() const; 
	~Tile() {
		if (this->mine != nullptr) {
			delete mine;
		}
	}
};

