#include "RenderMap.h"


void RenderMap::update() {

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			//Calculate which tile is currently being iterated through
			int tileX = (int)(x / tileLength);
			int tileY = (int)(z / tileLength);

			//Only apply perlin noise if the surface is swimmable			
			if (map.getTile(tileX + dimensions * tileY).getProperties().SWIMMABLE) {
				float y = n.noise(x / 50.0 + current, z / 50.0) * 3000.0 - 1000;

				vertices[offset] = Vector3(
					10 * x * HEIGHTMAP_X, y, 10 * z * HEIGHTMAP_Z);
			}
			else {

				vertices[offset] = Vector3(
					10 * x * HEIGHTMAP_X, 10 * HEIGHTMAP_Y, 10 * z * HEIGHTMAP_Z);

			}

			textureCoords[offset] = Vector2(
				x * HEIGHTMAP_TEX_X + current, z * HEIGHTMAP_TEX_Z);

		}

	}

	//glUniform3fv(*yLocations, sizeof(int) * numVertices, (const GLfloat*)yLocations);

	current += PERLIN_STEP;

	BufferData();

}