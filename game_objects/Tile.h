#pragma once

//enum class TileType { COBBLESTONE, LAVA, WATER, TERRAIN_GRASS, TERRAIN_SNOW };
enum class TileType { LAND, WATER, START, FINISH, INACTIVE, ACTIVE, CONFIRM, SWAP };

//struct Properties {
//	bool WALKABLE; // Can the tile be walked on
//	bool SWIMMABLE; // This will determine whether the swim animations are triggered or not
//	float DAMAGE_OUTPUT; // This is the amount of damage the tile will output to the character, if any
//	float MOVEMENT_DAMPEN; // This is how much the tile will slow the player, if any
//};

class Tile {

private:
	TileType type;
	//Properties properties;

public:
	Tile() {}

	Tile(TileType type/*, bool walkable, bool swimmable, float damageOutput, float movementDampen*/) {

		this->type = type;
		//setProperties(walkable, swimmable, damageOutput, movementDampen);

	}

	TileType getType() { return type; }
	//Properties getProperties() { return properties; }

	void setType(TileType type) { this->type = type; }
	/*void setProperties(bool walkable, bool swimmable, float damageOutput, float movementDampen) {
		Properties props = Properties();

		props.WALKABLE = walkable;
		props.SWIMMABLE = swimmable;
		props.DAMAGE_OUTPUT = damageOutput;
		props.MOVEMENT_DAMPEN = movementDampen;

		properties = props;
	}*/

};