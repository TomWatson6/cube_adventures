#pragma once
#include "HeightMap.h"
#include "../game_objects/Map.h"
#include "PerlinNoise.h"

enum class MapType { WALKABLE, WATER, LAVA };

static const float PULSE_UPDATE = 2.0 / 255.0;
static const float COMPLETE_COLOUR = 50.0 / 255.0;

class RenderMap : public HeightMap {

private:

	const float MINIMUM_LEVEL = -5.0;
	const float LEVEL_DIFFERENCE = 100.0;

	bool increase = false;
	float extra = 0;

	Vector4 * baseColours;

	int index;
	int dimensions;
	float tileLength;
	//float yPos = 10 * HEIGHTMAP_Y;
	float waterLevel = -3.0;

	Map map;
	MapType mapType;

	bool* isWater;
	float* heights = new float[RAW_WIDTH * RAW_HEIGHT];
	//vector<float> heights;

	PerlinNoise p = PerlinNoise();

	//Todo -- Set these in constructor / update methods
	float perlinCurrent = 0;
	float perlinStep = 0;

public:

	RenderMap() {};

	RenderMap(int index, Map map, MapType mapType, string name) : HeightMap(name) {

		this->index = index;
		this->dimensions = map.getDimensions();
		this->tileLength = RAW_WIDTH / dimensions;
		this->map = map;
		this->mapType = mapType;


		isWater = new bool[dimensions * dimensions];

		for (int i = 0; i < dimensions; i++) {
			for (int j = 0; j < dimensions; j++) {
				isWater[i * dimensions + j] = map.getTile(i * dimensions + j).getType() == TileType::WATER;
			}
		}

		baseColours = new Vector4[RAW_WIDTH * RAW_HEIGHT];

		for (int x = 0; x < RAW_WIDTH; x++) {
			for (int z = 0; z < RAW_HEIGHT; z++) {

				int offset = x * RAW_WIDTH + z;

				//Calculate which tile is currently being iterated through
				int tileX = (int)(x / tileLength);
				int tileZ = (int)(z / tileLength);

				int currentTile = tileX * dimensions + tileZ;

				if (map.getTile(currentTile).getType() == TileType::INACTIVE) {
					colours[offset] = colourInteractiveTile(currentTile, offset,
						Vector3(180.0 / 255.0, 0, 0),
						Vector3(120.0 / 255.0, 0, 0));
				}
				else if (map.getTile(currentTile).getType() == TileType::ACTIVE) {
					colours[offset] = colourInteractiveTile(currentTile, offset,
						Vector3(0, 180.0 / 255.0, 0),
						Vector3(0, 120.0 / 255.0, 0));
				}
				else if (map.getTile(currentTile).getType() == TileType::SWAP) {
					colours[offset] = colourInteractiveTile(currentTile, offset,
						Vector3(0, 0, 180.0 / 255.0),
						Vector3(0, 0, 120.0 / 255.0));
				}
				else if (map.getTile(currentTile).getType() == TileType::RESET) {
					colours[offset] = colourInteractiveTile(currentTile, offset,
						Vector3(152.0 / 255.0, 0, 1),
						Vector3(96.0 / 255.0, 0, 160.0 / 255.0));
				}
				else if (map.getTile(currentTile).getType() == TileType::CONFIRM) {
					colours[offset] = colourInteractiveTile(currentTile, offset,
						Vector3(1, 153.0 / 255.0, 0),
						Vector3(204.0 / 255.0, 122.0 / 255.0, 0));
				}
				else if (map.getTile(currentTile).getType() == TileType::TELEPORT) {
					colours[offset] = colourInteractiveTile(currentTile, offset,
						Vector3(1, 233.0 / 255.0, 35.0 / 255.0),
						Vector3(214.0 / 255.0, 193.0 / 255.0, 4.0 / 255.0));
				}
				else if (map.getTile(currentTile).getType() == TileType::ILLEGAL) {
					colours[offset] = Vector4(0.1, 0.1, 0.1, 1);
				}
				else if (map.getTile(currentTile).getType() == TileType::WATER) {
					colours[offset] = Vector4(0, 0, 1, 1);
				}
				else {
					colours[offset] = Vector4(0.3, 0.3, 0.3, 1);
				}

				baseColours[offset] = colours[offset];

				//Only apply perlin noise if the surface is swimmable
				if (isWater[tileX * dimensions + tileZ]) {
					heights[x * RAW_WIDTH + z] = n.noise(x / 50.0 + current, z / 50.0) * 1000.0;
				}
				else {
					heights[x * RAW_WIDTH + z] = 10 * HEIGHTMAP_Y;
				}

			}
		}

	}

	~RenderMap() {

		delete[] isWater;
		delete[] heights;

	}

	float getCurrent() { return current; }
	int getIndex() { return index; }
	int getDimensions() { return dimensions; }
	float getTileLength() { return tileLength; }
	Map getMap() { return map; }
	vector<Tile> getTiles() { return map.getTiles(); }
	Tile getTile(int index) { return map.getTile(index); }
	Vector4 colourInteractiveTile(int currentTile, int offset, Vector3 innerColour, Vector3 outerColour);
	void setColour(int offset, Vector4 colour) { colours[offset] = colour; }

	void setIndex(int index) { this->index = index; }
	void setDimensions(int dimensions) { this->dimensions = dimensions; this->tileLength = (float)RAW_WIDTH / dimensions; }

	void reduceBaseColours();

	void updateHeights();

	void update();

	//Methods to determine tile heights
	void setWalkableHeight(Vector2 &startXY, // Top left corner of the tile
		Vector2 &endXY, // Bottom right corner of the tile
		float level,
		int currentTile); // The higher the level, the greater the height of the tile - useful for wall/walkable surface differentiation


	void setSwimmableHeight(Vector2 startXY, // Top left corner of the tile
		Vector2 endXY, // Bottom right corner of the tile
		float level, // The higher the level, the greater the height of the tile - useful for lava/water surface differentiation
		float variation, // As this will use Perlin Noise, this will determine the min/max values it can go between
		float offsetSpeedNoise, // This will determine how quickly the perlin noise will move
		float offsetSpeedTexture,
		int currentTile); //This will determine how quickly the texture will move

	void pulse(int tileIndex, float magnitude);

	void negateTile(int tileIndex);

	void colourFinishTile();

};