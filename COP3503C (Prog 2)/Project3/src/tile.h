#pragma once
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
public:
	const int x;
	const int y;
	struct AdjacentTiles {
		Tile* adjacent[8];
	};
	AdjacentTiles tiles;
	Tile(int x, int y, Mine* mine):
		// only use if initializing as mine.
		mine(mine),
		adjacent_mines(0),
		current_state(TILE_STATE::HIDDEN),
		x(x), y(y), 
		tiles( AdjacentTiles { .adjacent = {} } )
	{};
	Tile(int x, int y):
		mine(nullptr),
		adjacent_mines(0),
		current_state(TILE_STATE::HIDDEN),
		x(x), y(y),
		tiles( AdjacentTiles { .adjacent = {} } )
	{};

	std::string as_str() {
		std::string has_a_mine = this->has_mine() ? "true" : "false";
		std::string output_msg = "Tile { x = " 
			+ std::to_string(this->x) + ", y = " 
			+ std::to_string(y) + ", has_mine = " + has_a_mine + ", adjacent_mines = " 
			+ std::to_string(this->adjacent_mines) + " }";
		return output_msg;
	}

	void plant_mine() {
		this->mine = new Mine(this->x, this->y);
	}

	void incr_adj_mine_counts() {
		// assumes current tile has a mine.

		if (!this->has_mine()) {
			throw std::runtime_error("Cannot increment adjacent mine counts if starting Tile is not a mine!");
		}

		for (size_t i = 0; i < 8; i++) {
			if (this->tiles.adjacent[i] != nullptr) {
				if (!this->tiles.adjacent[i]->has_mine()) {
					this->tiles.adjacent[i]->adjacent_mines++;
				}
			}
		}
	}

	void reveal_tile() {
		// use this when revealing tiles without mines
		this->current_state = TILE_STATE::REVEALED;
	}

	bool has_mine() const {
		return mine != nullptr;
	};

	bool has_detonated() const {
		if (!this->has_mine()) {
			throw std::runtime_error("Mine does not exist on this Tile. Cannot detonate.");
		}
		return this->mine->has_detonated;
	}

	TILE_STATE get_state() const {
		return this->current_state;
	}

	int get_adjacent_mines() const {
		return this->adjacent_mines;
	}

	bool get_is_flagged() const {
		return this->flagged;
	}

	void set_flag_state(bool is_flagged) {
		if (this->current_state == TILE_STATE::REVEALED) {
			throw std::runtime_error("Cannot flag a tile that has already been revealed!");
		}
		this->flagged = is_flagged;
	}

	void detonate_mine() {
		if (!this->has_mine()) {
			throw std::runtime_error("Mine does not exist! Cannot detonate");
		}
		this->mine->has_detonated = true;
		this->current_state = TILE_STATE::REVEALED;
	}

	void assign_neighboring_tiles(
		const std::vector<std::vector<Tile*>>& board
	) {
		size_t max_rows = board.size();
		if (max_rows == 0) {
			throw std::runtime_error("Board uninitialized! Cannot compute neighboring tiles.");
		}
		size_t max_cols = board.at(0).size();
		size_t row = this->y;
		size_t col = this->x;
		size_t col_start, col_end;
		size_t row_start, row_end;
		col_start = std::max(static_cast<int>(col) - 1, 0);
		col_end = std::min(static_cast<int>(col) + 2, static_cast<int>(max_cols)); // for loop bounds
		row_start = std::max(static_cast<int>(row) - 1, 0);
		row_end = std::min(static_cast<int>(row) + 2, static_cast<int>(max_rows));
		size_t count = 0;
		for (size_t r = row_start; r < row_end; r++) {
			for (size_t c = col_start ; c < col_end; c++) {
				if (c == col && r == row) {
					continue;
				}
				this->tiles.adjacent[count++] = board.at(r).at(c);
			}
		}
	}

	AdjacentTiles get_neighbors() const {
		return this->tiles;
	}

	~Tile() {
		if (this->mine != nullptr) {
			delete mine;
		}
	}
};

