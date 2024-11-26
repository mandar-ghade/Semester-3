#include "tile.h"

MINE_DISTANCE mine_distance_as_literal(int distance) {
	switch (distance) {
		case 0:
			return MINE_DISTANCE::NONE;
		case 1:
			return MINE_DISTANCE::ONE_AWAY;
		case 2:
			return MINE_DISTANCE::TWO_AWAY;
		case 3:
			return MINE_DISTANCE::THREE_AWAY;
		case 4:
			return MINE_DISTANCE::FOUR_AWAY;
		case 5:
			return MINE_DISTANCE::FIVE_AWAY;
		case 6:
			return MINE_DISTANCE::SIX_AWAY;
		case 7:
			return MINE_DISTANCE::SEVEN_AWAY;
		case 8:
			return MINE_DISTANCE::EIGHT_AWAY;
		default:
			throw std::runtime_error("Incorrect mine distance!");
	}
}

