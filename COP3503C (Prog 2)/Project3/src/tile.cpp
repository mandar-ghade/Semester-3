#include "tile.h"


sf::Sprite& Tile::get_sprite() {
	return this->sprite;
}

std::string Tile::as_str() const {
	std::string has_a_mine = this->has_mine() ? "true" : "false";
	std::string output_msg = "Tile { x = " 
		+ std::to_string(this->x) + ", y = " 
		+ std::to_string(y) + ", has_mine = " + has_a_mine + ", adjacent_mines = " 
		+ std::to_string(this->adjacent_mines) + " }";
	return output_msg;
}

void Tile::plant_mine() {
	this->mine = new Mine(this->x, this->y);
	//this->sprite.setTexture(this->cfg.textures.mine);
}

void Tile::set_matching_texture() {
	if (this->has_mine()) {
		this->sprite.setTexture(this->cfg.textures.mine);
		return;
	}
	if (this->adjacent_mines == 1) {
		this->sprite.setTexture(this->cfg.textures.number_1);
	} else if (this->adjacent_mines == 2) {
		this->sprite.setTexture(this->cfg.textures.number_2);
	} else if (this->adjacent_mines == 3) {
		this->sprite.setTexture(this->cfg.textures.number_3);
	} else if (this->adjacent_mines == 4) {
		this->sprite.setTexture(this->cfg.textures.number_4);
	} else if (this->adjacent_mines == 5) {
		this->sprite.setTexture(this->cfg.textures.number_5);
	} else if (this->adjacent_mines == 6) {
		this->sprite.setTexture(this->cfg.textures.number_6);
	} else if (this->adjacent_mines == 7) {
		this->sprite.setTexture(this->cfg.textures.number_7);
	} else if (this->adjacent_mines == 8) {
		this->sprite.setTexture(this->cfg.textures.number_8);
	} 
}

void Tile::incr_adj_mine_counts() const {
	// assumes current tile has a mine.

	if (!this->has_mine()) {
		throw std::runtime_error("Cannot increment adjacent mine counts if starting Tile is not a mine!");
	}

	for (size_t i = 0; i < 8; i++) {
		if (this->tiles.adjacent[i] != nullptr) {
			if (!this->tiles.adjacent[i]->has_mine()) {
				this->tiles.adjacent[i]->adjacent_mines++;
				//this->tiles.adjacent[i]->set_matching_texture();
			}
		}
	}
}

void Tile::reveal_tile() {
	// use this when revealing tiles without mines
	if (this->has_mine()) {
		throw std::runtime_error("Attempted to reveal a mine-containing tile. Use detonate() instead.");
	}
	this->current_state = TILE_STATE::REVEALED;
}

bool Tile::has_mine() const {
	return mine != nullptr;
};

bool Tile::has_detonated() const {
	if (!this->has_mine()) {
		throw std::runtime_error("Mine does not exist on this Tile. Cannot detonate.");
	}
	return this->mine->has_detonated;
}

TILE_STATE Tile::get_state() const {
	return this->current_state;
}

int Tile::get_adjacent_mines() const {
	return this->adjacent_mines;
}

bool Tile::get_is_flagged() const {
	return this->flagged;
}

void Tile::set_flag_state(bool is_flagged) {
	if (this->current_state == TILE_STATE::REVEALED) {
		throw std::runtime_error("Cannot flag a tile that has already been revealed!");
	}
	this->flagged = is_flagged;
}

void Tile::detonate_mine() {
	if (!this->has_mine()) {
		throw std::runtime_error("Mine does not exist! Cannot detonate");
	}
	this->mine->has_detonated = true;
	this->current_state = TILE_STATE::REVEALED;
}

void Tile::assign_neighboring_tiles(
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

Tile::AdjacentTiles Tile::get_neighbors() const {
	return this->tiles;
}

