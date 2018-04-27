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
		heights[i] = -p.noise(i / 50.0 + current, RAW_HEIGHT - 1 / 50.0) * 1000.0 + 500;
		//n.noise(i / 50.0 + current, RAW_HEIGHT - 1 / 50.0) * 1000.0 - 333
	}

}

Vector4 RenderMap::colourInteractiveTile(int currentTile,
	int offset, Vector3 innerColour, Vector3 outerColour) {

	float tileWidth = (10 * HEIGHTMAP_X * (RAW_WIDTH - 1)) / dimensions;

	float xPos = ((currentTile % dimensions) + 0.5) * tileWidth;
	float yPos = ((currentTile / dimensions) + 0.5) * tileWidth;

	float offsetX = (offset % RAW_WIDTH) * (10 * HEIGHTMAP_X);
	float offsetY = (offset / RAW_WIDTH) * (10 * HEIGHTMAP_X);

	float xDiff = abs(xPos - offsetX);
	float yDiff = abs(yPos - offsetY);

	float dist = sqrt(xDiff * xDiff + yDiff * yDiff);
	float maxDist = sqrt(0.5 * tileWidth * 0.5 * tileWidth * 2.0);

	Vector3 interpolationVector = outerColour - innerColour;

	interpolationVector = interpolationVector * dist / maxDist;

	interpolationVector += outerColour;

	Vector4 toReturn = Vector4(interpolationVector.x, interpolationVector.y,
		interpolationVector.z, 1);

	return toReturn;

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

			Vector3 vectorA = Vector3(colours[offset].x, colours[offset].y, colours[offset].z);
			Vector3 vectorB = Vector3(baseColours[offset].x, baseColours[offset].y, baseColours[offset].z);

			/*if (vectorA != vectorB) {
				if (colours[offset].x > 0) {
					colours[offset].x -= PULSE_UPDATE;
				} else if (colours[offset].y > 0) {
					colours[offset].y -= PULSE_UPDATE;
				} else if (colours[offset].z > 0) {
					colours[offset].z -= PULSE_UPDATE;
				}
			}*/

			if (colours[offset].x > baseColours[offset].x) {
				colours[offset].x -= PULSE_UPDATE;
			}
			if (colours[offset].y > baseColours[offset].y) {
				colours[offset].y -= PULSE_UPDATE;
			}
			if (colours[offset].z > baseColours[offset].z) {
				colours[offset].z -= PULSE_UPDATE;
			}

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

void RenderMap::pulse(int tileIndex, float magnitude) {

	Vector3 pulseColour = Vector3(magnitude, magnitude, magnitude);

	int startX = (tileIndex % dimensions) * tileLength;
	int endX = (tileIndex % dimensions) * tileLength + tileLength;

	int startY = (tileIndex / dimensions) * tileLength;
	int endY = (tileIndex / dimensions) * tileLength + tileLength;


	for (int i = startX; i < endX; i++) {
		for (int j = startY; j < endY; j++) {
			int offset = j * RAW_WIDTH + i;
			Vector3 currentColour = Vector3(colours[offset].x, colours[offset].y, colours[offset].z);
			currentColour += pulseColour;
			colours[offset] = Vector4(currentColour.x, currentColour.y, currentColour.z, 1);
		}
	}

}

void RenderMap::reduceBaseColours() {

	Vector3 reductionColour = Vector3(COMPLETE_COLOUR, COMPLETE_COLOUR, COMPLETE_COLOUR);

	for (int i = 0; i < dimensions * dimensions; i++) {

		TileType type = map.getTile(i).getType();

			if (type == TileType::INACTIVE || type == TileType::ACTIVE || type == TileType::SWAP) {

				int startX = (i % dimensions) * RAW_WIDTH / dimensions;
				int endX = (i % dimensions) * RAW_WIDTH / dimensions + RAW_WIDTH / dimensions;

				int startY = (i / dimensions) * RAW_WIDTH / dimensions;
				int endY = (i / dimensions) * RAW_WIDTH / dimensions + RAW_WIDTH / dimensions;


				for (int j = startX; j < endX; j++) {
					for (int k = startY; k < endY; k++) {
						int offset = k * RAW_WIDTH + j;
						Vector3 currentColour = Vector3(baseColours[offset].x, baseColours[offset].y, baseColours[offset].z);
						currentColour -= reductionColour;
						baseColours[offset] = Vector4(currentColour.x, currentColour.y, currentColour.z, 1);
					}
				}

			}

	}

}

void RenderMap::negateTile(int tileIndex) {

	int startX = (tileIndex % dimensions) * RAW_WIDTH / dimensions;
	int endX = (tileIndex % dimensions) * RAW_WIDTH / dimensions + RAW_WIDTH / dimensions;

	int startY = (tileIndex / dimensions) * RAW_WIDTH / dimensions;
	int endY = (tileIndex / dimensions) * RAW_WIDTH / dimensions + RAW_WIDTH / dimensions;

	if (map.getTile(tileIndex).getType() == TileType::INACTIVE) {
		map.setTile(tileIndex, Tile(TileType::ACTIVE));

		for (int i = startX; i < endX; i++) {
			for (int j = startY; j < endY; j++) {
				
				int offset = j * RAW_WIDTH + i;

				baseColours[offset] = colourInteractiveTile(tileIndex, offset,
					Vector3(0, 180.0 / 255.0, 0),
					Vector3(0, 120.0 / 255.0, 0));

				colours[offset] = colourInteractiveTile(tileIndex, offset,
					Vector3(0, 180.0 / 255.0, 0),
					Vector3(0, 120.0 / 255.0, 0));

			}
		}

	}
	else {
		map.setTile(tileIndex, Tile(TileType::INACTIVE));

		for (int i = startX; i < endX; i++) {
			for (int j = startY; j < endY; j++) {

				int offset = j * RAW_WIDTH + i;

				baseColours[offset] = colourInteractiveTile(tileIndex, offset,
					Vector3(180.0 / 255.0, 0, 0),
					Vector3(120.0 / 255.0, 0, 0));

				colours[offset] = colourInteractiveTile(tileIndex, offset,
					Vector3(180.0 / 255.0, 0, 0),
					Vector3(120.0 / 255.0, 0, 0));

			}
		}

	}

}

void RenderMap::colourFinishTile() {

	int tileIndex;

	for (int i = 0; i < dimensions * dimensions; i++) {
		if (map.getTile(i).getType() == TileType::FINISH) {
			tileIndex = i;
			break;
		}
	}

	int startX = (tileIndex % dimensions) * RAW_WIDTH / dimensions;
	int endX = (tileIndex % dimensions) * RAW_WIDTH / dimensions + RAW_WIDTH / dimensions;

	int startY = (tileIndex / dimensions) * RAW_WIDTH / dimensions;
	int endY = (tileIndex / dimensions) * RAW_WIDTH / dimensions + RAW_WIDTH / dimensions;

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {

			int offset = x + RAW_WIDTH * y;

			colours[offset] = colourInteractiveTile(tileIndex, offset,
				Vector3(0, 227.0 / 255.0, 252.0 / 255.0),
				Vector3(0, 156.0 / 255.0, 173.0 / 255.0));

			baseColours[offset] = colourInteractiveTile(tileIndex, offset,
				Vector3(0, 227.0 / 255.0, 252.0 / 255.0),
				Vector3(0, 156.0 / 255.0, 173.0 / 255.0));

		}
	}

}