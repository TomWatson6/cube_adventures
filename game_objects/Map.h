#pragma once
#include "Tile.h"
#include <vector>

using namespace std;

class Map {

private:
	int index; // What is the index of the map in the chain of 6 maps on the cube
	int dimensions; // The amount of tiles on the width/height of the map
	vector<Tile> tiles; // Vector of tiles to store all tiles on the map
	int startTile = 0;

public:
	Map() {}

	Map(int index, int dimensions, Tile* tiles) {

		this->index = index;
		this->dimensions = dimensions;

		//tiles = new Tile[dimensions * dimensions];

		for (int i = 0; i < dimensions; i++) {
			for (int j = 0; j < dimensions; j++) {
				this->tiles.push_back(tiles[i + j * dimensions]);
				if (this->tiles.at(i + j * dimensions).getType() == TileType::START)
					startTile = i + j * dimensions;
			}
		}

	}

	int getIndex() { return index; }
	int getDimensions() { return dimensions; }
	vector<Tile> getTiles() { return tiles; }
	Tile getTile(int index) { return tiles.at(index); }
	int getStartTile() { return startTile; }

	void setIndex(int index) { this->index = index; }
	void setDimensions(int dimensions) { this->dimensions = dimensions; }
	void setTiles(vector<Tile> tiles) {	this->tiles = tiles; }
	void setStartTile(int startTile) { this->startTile = startTile; }

};