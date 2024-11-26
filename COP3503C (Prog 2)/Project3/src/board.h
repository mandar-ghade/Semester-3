#pragma once
#include <map>
#include <vector>
#include "config.h"
#include "tile.h"


class Board {
private:
	const size_t rows;
	const size_t columns;
	const size_t mine_count;
	std::vector<std::vector<Tile*>> tiles;
	std::vector<Tile*> mines;
public:
	Board(Config& cfg): 
		rows(cfg.rows),
		columns(cfg.columns),
		mine_count(cfg.mines)
	{
		generate_board();
	}

	void generate_board() {
		for (size_t i = 0; i < this->rows; i++) {
			tiles.push_back(std::vector<Tile*>());
			for (size_t j = 0; j < this->columns; j++) {
				tiles.at(i).push_back(
					new Tile((int)j, (int)i)
				);
			}
		}
		this->assign_neighboring_tiles();
	}

	void assign_neighboring_tiles() {
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				(*col)->assign_neighboring_tiles(tiles);
			}
		}
	}

	Tile::AdjacentTiles get_neighboring(Tile* tile) {
		return tile->get_neighbors();
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
		//std::cout << "\tmines = " << this->mine_count << ",\n}\n";
	}

	~Board() {
		for (auto row = tiles.begin(); row != tiles.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				delete (*col);
			}
		}
	}

};
