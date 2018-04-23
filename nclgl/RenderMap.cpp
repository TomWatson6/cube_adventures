#include "RenderMap.h"

void RenderMap::update() {

	updateHeights();

	for (int x = 0; x < dimensions; x++) {
		for (int z = 0; z < dimensions; z++) {

			if (isWater[x * dimensions + z]) {
				setSwimmableHeight(Vector2(x * tileLength, z * tileLength),
					Vector2(x * tileLength + tileLength, z * tileLength + tileLength), -3.0f, 0, 0, 0, x * dimensions + z);
			}
			else {
				setWalkableHeight(Vector2(x * tileLength, z * tileLength),
					Vector2(x * tileLength + tileLength, z * tileLength + tileLength), 0, x * dimensions + z);
			}

		}
	}

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			//Calculate which tile is currently being iterated through
			//int tileX = (int)(x / tileLength);
			//int tileY = (int)(z / tileLength);

			//

			////Only apply perlin noise if the surface is swimmable			
			//if (map.getTile(tileX + dimensions * tileY).getProperties().SWIMMABLE) {
			//	

			//	vertices[offset] = Vector3(
			//		10 * x * HEIGHTMAP_X, yPos, 10 * z * HEIGHTMAP_Z);
			//}
			//else {

			//	vertices[offset] = Vector3(
			//		10 * x * HEIGHTMAP_X, 10 * HEIGHTMAP_Y, 10 * z * HEIGHTMAP_Z);

			//}

			textureCoords[offset] = Vector2(
				x * HEIGHTMAP_TEX_X + current, z * HEIGHTMAP_TEX_Z);

		}

	}

	current += PERLIN_STEP;
	//current = 0;

	RebufferData();

}

void RenderMap::updateHeights() {

	//Delete a row of heights
	for (int i = 0; i < RAW_WIDTH; i++) {
		//delete &heights[i];
		//heights[i] = NULL;
	}

	//Shuffle all values down to correct places in the array (O(N - sqrt(N)))
	for (int i = RAW_WIDTH; i < RAW_WIDTH * RAW_HEIGHT; i++) {
		heights[i - RAW_WIDTH] = heights[i];
	}

	//Add new row at the end of the array using perlin noise function (O(sqrt(N)) * O(noise))
	for (int i = RAW_WIDTH * RAW_HEIGHT - RAW_WIDTH; i < RAW_WIDTH * RAW_HEIGHT; i++) {
		heights[i] = p.noise(i / 50.0 + current, RAW_HEIGHT - 1 / 50.0) * 1000.0 - 333;
		//n.noise(i / 50.0 + current, RAW_HEIGHT - 1 / 50.0) * 1000.0 - 333
	}

}

void RenderMap::setWalkableHeight(Vector2 &startXY, Vector2 &endXY, float level, int currentTile) {

	float tileBaseHeight = level * LEVEL_DIFFERENCE;

	for (int x = startXY.x; x < endXY.x; x++) {
		for (int z = startXY.y; z < endXY.y; z++) {

			int offset = (x * RAW_WIDTH) + z;

			float xPos = 10 * x * HEIGHTMAP_X;

			vertices[offset] = Vector3(
				xPos,
				tileBaseHeight,
				10 * z * HEIGHTMAP_Z
			);

			if (map.getTile(currentTile).getType() == TileType::LAND) {
				colours[offset] = Vector4(0.3, 0.3, 0.3, 255);
			}
			else {
				


			}

			//colours[offset] = Vector4(0.3, 0.3, 0.3, 255);

		}
	}

}

void RenderMap::setSwimmableHeight(Vector2 startXY, Vector2 endXY, float level, float variation, float offsetSpeedNoise, float offsetSpeedTexture, int currentTile) {

	float tileBaseHeight = level * LEVEL_DIFFERENCE;

	for (int x = startXY.x; x < endXY.x; x++) {
		for (int z = startXY.y; z < endXY.y; z++) {

			float xPos = 10 * x * HEIGHTMAP_X;

			int offset = (x * RAW_WIDTH) + z;

			vertices[offset] = Vector3(
				xPos,
				heights[x * RAW_WIDTH + z] + tileBaseHeight,
				10 * z * HEIGHTMAP_Z
			);

			colours[offset] = Vector4(0, 0, 1, 1);

		}
	}

}