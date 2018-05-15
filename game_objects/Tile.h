#pragma once

enum TileType { LAND, WATER, START, FINISH, INACTIVE, ACTIVE, CONFIRM, SWAP, RESET, ILLEGAL, TELEPORT };

class Tile {

private:
	TileType type;
	//Properties properties;

public:
	Tile() {}

	Tile(TileType type) {

		this->type = type;

	}

	TileType getType() { return type; }

	void setType(TileType type) { 
		if (type == TileType::INACTIVE) {
			this->type = static_cast<TileType>(this->type + 1);
		}
		else if (type == TileType::ACTIVE) {
			this->type = static_cast<TileType>(this->type - 1);
		}
	}

};