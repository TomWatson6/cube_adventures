# include "HeightMap.h"
#include <math.h>

HeightMap::HeightMap(std::string name) {
	std::ifstream file(name.c_str(), ios::binary);
	if (!file) {
		return;
	}
	numVertices = RAW_WIDTH * RAW_HEIGHT;
	numIndices = (RAW_WIDTH - 1)*(RAW_HEIGHT - 1) * 6;
	vertices = new Vector3[numVertices];
	textureCoords = new Vector2[numVertices];
	colours = new Vector4[numVertices];
	indices = new GLuint[numIndices];
	unsigned char * data = new unsigned char[numVertices];

	file.read((char *)data, numVertices * sizeof(unsigned char));
	file.close();

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			float y = n.noise(x / 50.0 + current, z / 50.0) * 5000.0;

			vertices[offset] = Vector3(
				10*x * HEIGHTMAP_X, y, 10*z * HEIGHTMAP_Z);

			textureCoords[offset] = Vector2(
				x * HEIGHTMAP_TEX_X, z * HEIGHTMAP_TEX_Z);

			//Make a method to generate colours with perlin noise for lava
			colours[offset] = Vector4(255, 255, 0, 255);

		}

	}

	delete data;
	numIndices = 0;

	for (int x = 0; x < RAW_WIDTH - 1; ++x) {
		for (int z = 0; z < RAW_HEIGHT - 1; ++z) {
			int a = (x * (RAW_WIDTH)) + z;
			int b = ((x + 1) * (RAW_WIDTH)) + z;
			int c = ((x + 1) * (RAW_WIDTH)) + (z + 1);
			int d = (x * (RAW_WIDTH)) + (z + 1);

			indices[numIndices++] = c;
			indices[numIndices++] = b;
			indices[numIndices++] = a;

			indices[numIndices++] = a;
			indices[numIndices++] = d;
			indices[numIndices++] = c;

		}

	}

	//current += PERLIN_STEP;

	BufferData();

}

void HeightMap::update() {

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			//Todo -- Make constants for magic numbers
			float y = n.noise(x / 50.0 + current, z / 50.0) * 500.0;

			vertices[offset] = Vector3(
				10 * x * HEIGHTMAP_X, y, 10 * z * HEIGHTMAP_Z);

			textureCoords[offset] = Vector2(
				x * HEIGHTMAP_TEX_X /*+ current*/, z * HEIGHTMAP_TEX_Z);

		}

	}

	

	//glUniform3fv(*yLocations, sizeof(int) * numVertices, (const GLfloat*)yLocations);

	//current += PERLIN_STEP;

	BufferData();

}