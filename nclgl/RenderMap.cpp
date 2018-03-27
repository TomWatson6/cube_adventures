#include "RenderMap.h"

void RenderMap::update() {

	for (int x = 0; x < dimensions; x++) {
		for (int z = 0; z < dimensions; z++) {

			if (isSwimmable[x + dimensions * z]) {
				setSwimmableHeight(Vector2(x * tileLength, z * tileLength),
					Vector2(x * tileLength + tileLength, z * tileLength + tileLength), -3.0f, 0, 0, 0);
			}
			else {
				setWalkableHeight(Vector2(x * tileLength, z * tileLength),
					Vector2(x * tileLength + tileLength, z * tileLength + tileLength), 0);
				//(x * tileLength) + (z * tileLength * RAW_WIDTH)
				//(x * tileLength + tileLength) + (z * tileLength * RAW_WIDTH + tileLength)
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

	//glUniform3fv(*yLocations, sizeof(int) * numVertices, (const GLfloat*)yLocations);

	current += PERLIN_STEP;

	BufferData();

}

void RenderMap::setWalkableHeight(Vector2 startXY, Vector2 endXY, float level) {

	float tileBaseHeight = level * LEVEL_DIFFERENCE;

	for (int x = startXY.x; x < endXY.x; x++) {
		for (int z = startXY.y; z < endXY.y; z++) {

			int offset = (x * RAW_WIDTH) + z;

			vertices[offset] = Vector3(
				10 * x * HEIGHTMAP_X,
				10 * HEIGHTMAP_Y + tileBaseHeight,
				10 * z * HEIGHTMAP_Z
			);

		}
	}

}

void RenderMap::setSwimmableHeight(Vector2 startXY, Vector2 endXY, float level, float variation, float offsetSpeedNoise, float offsetSpeedTexture) {

	float tileBaseHeight = level * LEVEL_DIFFERENCE;

	for (int x = startXY.x; x < endXY.x; x++) {
		for (int z = startXY.y; z < endXY.y; z++) {

			int offset = (x * RAW_WIDTH) + z;

			float y = n.noise(x / 50.0 + current, z / 50.0) * 1000.0 - 333;

			vertices[offset] = Vector3(
				10 * x * HEIGHTMAP_X,
				heights[x + RAW_WIDTH * z] + tileBaseHeight,
				10 * z * HEIGHTMAP_Z
			);

		}
	}

}