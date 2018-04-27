#pragma once
#include "Tile.h"
#include <vector>
#include <iostream>

using namespace std;

class Map {

private:
	int index; // What is the index of the map in the chain of 6 maps on the cube
	int dimensions; // The amount of tiles on the width/height of the map
	vector<Tile> tiles; // Vector of tiles to store all tiles on the map
	int startTile = 0;
	bool complete;

public:
	Map() {}

	Map(int index, int dimensions, vector<Tile> tiles) {

		this->index = index;
		this->dimensions = dimensions;
		this->tiles = tiles;
		this->complete = false;

		/*for (int i = 0; i < dimensions; i++) {
			for (int j = 0; j < dimensions; j++) {
				if (this->tiles.at(i * dimensions + j).getType() == TileType::START)
					startTile = i * dimensions + j;
			}
		}*/

		for (int i = 0; i < dimensions * dimensions; i++) {
			if (this->tiles.at(i).getType() == TileType::START)
				startTile = i;
		}

	}

	bool isComplete() { return complete; }
	int getIndex() { return index; }
	int getDimensions() { return dimensions; }
	vector<Tile> getTiles() { return tiles; }
	Tile getTile(int index) { return tiles.at(index); }
	int getStartTile() { return startTile; }

	void setComplete(bool complete) { this->complete = complete; cout << "WOOOOOHOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl; }
	void setIndex(int index) { this->index = index; }
	void setDimensions(int dimensions) { this->dimensions = dimensions; }
	void setTiles(vector<Tile> tiles) {	this->tiles = tiles; }
	void setTile(int tileIndex, Tile tile) { tiles.at(tileIndex) = tile; }
	void setStartTile(int startTile) { this->startTile = startTile; }

};