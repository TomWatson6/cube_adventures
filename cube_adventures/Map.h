#pragma once
#include "Tile.h"

class Map {

private:
	int index; // What is the index of the map in the chain of 6 maps on the cube
	int dimensions; // The amount of tiles on the width/height of the map
	Tile* tiles; // 2 Dimensional array to store all tiles on the map

public:
	Map();

	Map(int index, int dimensions, Tile* tiles) {

		this->index = index;
		this->dimensions = dimensions;

		tiles = new Tile[dimensions * dimensions];

		for (int i = 0; i < dimensions; i++) {
			for (int j = 0; j < dimensions; j++) {
				this->tiles[i + j * dimensions] = tiles[i + j * dimensions];
			}
		}

	}

	int getIndex() { return index; }
	int getDimensions() { return dimensions; }
	Tile* getTiles() { return tiles; }
	Tile getTile(int index) { return tiles[index]; }

	void setIndex(int index) { this->index = index; }
	void setDimensions(int dimensions) { this->dimensions = dimensions; }
	void setTiles(Tile* tiles) {

		for (int i = 0; i < dimensions * dimensions; i++) {
			this->tiles[i] = tiles[i];
		}

	}

};