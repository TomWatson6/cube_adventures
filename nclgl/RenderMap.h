#pragma once
#include "HeightMap.h"
#include "../game_objects/Map.h"
#include "PerlinNoise.h"

class RenderMap : public HeightMap {

private:

	float index;
	float dimensions;
	float tileLength = RAW_WIDTH / dimensions;
	float yPos = 10 * HEIGHTMAP_Y;

	Map map;

	PerlinNoise p = PerlinNoise();

	//Todo -- Set these in constructor / update methods
	float perlinCurrent = 0;
	float perlinStep = 0;

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

	//Methods to determine tile heights
	void setWalkableHeight(int startXY, // Top left corner of the tile
						int endXY, // Bottom right corner of the tile
						float level); // The higher the level, the greater the height of the tile - useful for wall/walkable surface differentiation
						
	
	void setSwimmableHeight(int startXY, // Top left corner of the tile
						int endXY, // Bottom right corner of the tile
						float level, // The higher the level, the greater the height of the tile - useful for lava/water surface differentiation
						float variation, // As this will use Perlin Noise, this will determine the min/max values it can go between
						float offsetSpeedNoise, // This will determine how quickly the perlin noise will move
						float offsetSpeedTexture); //This will determine how quickly the texture will move
						

};