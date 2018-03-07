#pragma once
#include "HeightMap.h"
#include "../game_objects/Map.h"

class RenderMap : public HeightMap {

private:

	float index;
	float dimensions;
	float tileLength = RAW_WIDTH / dimensions;

	Map map;

public:

	RenderMap(float index, Map map, string name) : HeightMap(name) {

		this->index = index;
		this->dimensions = map.getDimensions();
		this->tileLength = RAW_WIDTH / dimensions;
		this->map = map;

	}

	float getCurrent() { return current; }
	float getIndex() { return index; }
	float getDimensions() { return dimensions; }
	float getTileLength() { return tileLength; }
	Map getMap(int index) { return map; }
	vector<Tile> getTiles() { return map.getTiles(); }
	Tile getTile(int index) { return map.getTile(index); }

	void setIndex(float index) { this->index = index; }
	void setDimensions(float dimensions) { this->dimensions = dimensions; this->tileLength = RAW_WIDTH / dimensions; }

	void update();

};