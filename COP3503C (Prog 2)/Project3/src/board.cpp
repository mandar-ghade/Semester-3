#include "board.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include "config.h"
#include "tile.h"

void Board::generate_board() {
	for (size_t i = 0; i < (size_t)this->cfg->rows; i++) {
		tiles.push_back(std::vector<Tile>());
		for (size_t j = 0; j < (size_t)this->cfg->columns; j++) {
			tiles.at(i).push_back(
				Tile((int)j, (int)i, this->cfg->rows, this->cfg)
			);
		}
	}
	this->assign_neighboring_tiles();
	this->plant_mines();
}

void Board::assign_neighboring_tiles() {
	for (auto row = tiles.begin(); row != tiles.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			col->assign_neighboring_tiles(tiles);
		}
	}
}

void Board::plant_mines() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> row_dist(0, static_cast<int>(this->cfg->rows) - 1);
	std::uniform_int_distribution<> col_dist(0, static_cast<int>(this->cfg->columns) - 1);
	for (size_t i = 0; i < (size_t)this->cfg->mines; i++) {
		int row = row_dist(gen);
		int col = col_dist(gen);
		while (this->tiles[row][col].has_mine()) {
			row = row_dist(gen);
			col = col_dist(gen);
		}
		this->tiles[row][col].plant_mine();
		this->tiles[row][col].incr_adj_mine_counts();
	}
}

void Board::reset() {
	this->tiles.clear();
	generate_board();
}

void Board::draw_sprites(sf::RenderWindow* window, bool debug_mode, bool paused) {
	for (auto row = tiles.begin(); row != tiles.end(); row++) {
		for (auto tile = row->begin(); tile != row->end(); tile++) {
			if (!paused) {
				if (tile->get_background().getTexture() == &cfg->textures.hidden_tile) {
					if (!tile->get_is_hidden()) {
						tile->get_background().setTexture(&cfg->textures.tile_revealed);
					}
				}
				window->draw(tile->get_background());
				window->draw(tile->get_sprite());
			} else {
				tile->get_background().setTexture(&cfg->textures.tile_revealed);
				window->draw(tile->get_background());
				continue;
			}
			if (debug_mode && tile->get_is_hidden() && tile->has_mine()) {
				tile->get_top_layer().setTexture(&cfg->textures.mine);
				window->draw(tile->get_top_layer());
			}
			if (tile->get_is_flagged()) {
				tile->get_top_layer().setTexture(&cfg->textures.flag);
				window->draw(tile->get_top_layer());
			} 
		}
	}
}

void Board::print_as_str() {
	std::cout << "Board {" << '\n';
	std::cout << "\trows = " << this->cfg->rows << ',' << '\n';
	std::cout << "\tcolumns = " << this->cfg->columns << ',' << '\n';
	std::cout << "\tmines = " << this->cfg->mines << ',' << '\n';
	std::cout << "\tboard = " << "{" << '\n';
	for (auto row = tiles.begin(); row != tiles.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			std::cout << "\t\t" << col->as_str() << ',' << '\n';
			std::cout << "\t\t\tneighbors = {" << '\n';
			Tile::AdjacentTiles neighbors = col->get_neighbors();
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

Tile* Board::get_clicked_tile(const sf::Vector2i& rect) {
	for (auto row = tiles.begin(); row != tiles.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			if (col->get_sprite()
				.getGlobalBounds()
				.contains((float)rect.x,
						  (float)rect.y)) {
				return &*col;
			}
		}
	}
	return nullptr;
}

int Board::count_hidden_tiles() {
	int count = 0;
	for (auto row = this->tiles.begin(); row != this->tiles.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			if (col->get_is_hidden()) count++;
		}
	}
	return count;
}

int Board::count_flagged_tiles() {
	int count = 0;
	for (auto row = this->tiles.begin(); row != this->tiles.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			if (col->get_is_flagged()) count++;
		}
	}
	return count;
}

std::vector<Tile*> Board::get_mines() {
	std::vector<Tile*> mines;
	for (auto row = this->tiles.begin(); row != this->tiles.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			if (col->has_mine()) {
				mines.push_back(&*col);
			}
		}
	}
	return mines;
}

