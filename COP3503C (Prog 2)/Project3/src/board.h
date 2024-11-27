#pragma once
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
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
	void generate_board() {
		for (size_t i = 0; i < this->rows; i++) {
			tiles.push_back(std::vector<Tile*>());
			for (size_t j = 0; j < this->columns; j++) {
				tiles.at(i).push_back(
					new Tile((int)j, (int)i, (int)this->rows, this->cfg)
				);
			}
		}
		this->assign_neighboring_tiles();
		this->plant_mines();
	}

	void assign_neighboring_tiles() {
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				(*col)->assign_neighboring_tiles(tiles);
			}
		}
	}
	void plant_mines() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> row_dist(0, static_cast<int>(this->rows) - 1);
		std::uniform_int_distribution<> col_dist(0, static_cast<int>(this->columns) - 1);
		for (size_t i = 0; i < this->mine_count; i++) {
			int row = row_dist(gen);
			int col = col_dist(gen);
			while (this->tiles[row][col]->has_mine()) {
				row = row_dist(gen);
				col = col_dist(gen);
			}
			this->tiles[row][col]->plant_mine();
			this->mines.push_back(this->tiles[row][col]);
			this->tiles[row][col]->incr_adj_mine_counts();
		}
	}
public:
	Board(Config& cfg): 
		rows(cfg.rows),
		columns(cfg.columns),
		mine_count(cfg.mines),
		cfg(cfg)
	{
		generate_board();
	}
	void reset() {
		this->mines.clear();
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				delete (*col);
			}
		}
		this->tiles.clear();
		generate_board();
	}
	void draw_sprites(sf::RenderWindow& window) {
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				window.draw((*col)->get_sprite());
			}
		}
	}
	void print_as_str() {
		std::cout << "Board {" << '\n';
		std::cout << "\trows = " << this->rows << ',' << '\n';
		std::cout << "\tcolumns = " << this->columns << ',' << '\n';
		std::cout << "\tmines = " << this->mine_count << ',' << '\n';
		std::cout << "\tboard = " << "{" << '\n';
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				std::cout << "\t\t" << (*col)->as_str() << ',' << '\n';
				std::cout << "\t\t\tneighbors = {" << '\n';
				Tile::AdjacentTiles neighbors = (*col)->get_neighbors();
				for (size_t i = 0; i < 8; i++) {
					if (neighbors.adjacent[i] != nullptr) {
						std::cout << "\t\t\t\t" << neighbors.adjacent[i]->as_str() << '\n';
					}
				}
				std::cout << "\t\t\t}" << '\n';
			}
		}
		std::cout << "\t}\n"; 
		std::cout << "}\n";
	}

	~Board() {
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				delete (*col);
			}
		}
	}

};
