#pragma once
#include <iostream>
#include <vector>

enum MINE_DISTANCE {
	NONE, // not applicable, or has a bomb.
	ONE_AWAY,
	TWO_AWAY,
	THREE_AWAY,
	FOUR_AWAY,
	FIVE_AWAY,
	SIX_AWAY,
	SEVEN_AWAY,
	EIGHT_AWAY,
};

MINE_DISTANCE mine_distance_as_literal(int distance); 

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
	MINE_DISTANCE mine_distance;
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
		mine_distance(MINE_DISTANCE::NONE),
		current_state(TILE_STATE::HIDDEN),
		x(x), y(y), 
		tiles( AdjacentTiles { .adjacent = {} } )
	{};
	Tile(int x, int y):
		mine(nullptr),
		mine_distance(MINE_DISTANCE::NONE),
		current_state(TILE_STATE::HIDDEN),
		x(x), y(y),
		tiles( AdjacentTiles { .adjacent = {} } )
	{};

	std::string as_str() {
		std::string output_msg = "Tile { x = " + std::to_string(x) + ", y = " + std::to_string(y) + " }";
		return output_msg;
	}

	void plant_mine() {
		mine = new Mine(this->x, this->y);
	}

	bool has_mine() const {
		return mine != nullptr;
	};

	bool has_detonated() const {
		if (!this->has_mine()) {
			throw std::runtime_error("Mine does not exist on this Tile. Cannot debug its detonation");
		}
		return this->mine->has_detonated;
	}

	TILE_STATE get_state() const {
		return this->current_state;
	}

	MINE_DISTANCE get_mine_distance() const {
		if (this->has_mine()) {
			throw std::runtime_error("This tile has a mine! Cannot compute mine distance.");
		}
		return this->mine_distance;
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
		col_end = std::min(static_cast<int>(col) + 2, static_cast<int>(max_cols)); // +2 because not included i  for loop
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

