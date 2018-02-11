# include "HeightMap.h"
#include <math.h>
#include "PerlinNoise.h"

const float PERLIN_STEP = 0.05;
float current = 0;
PerlinNoise n = PerlinNoise();

HeightMap::HeightMap(std::string name) {
	std::ifstream file(name.c_str(), ios::binary);
	if (!file) {
		return;
	}
	numVertices = RAW_WIDTH * RAW_HEIGHT;
	numIndices = (RAW_WIDTH - 1)*(RAW_HEIGHT - 1) * 6;
	vertices = new Vector3[numVertices];
	textureCoords = new Vector2[numVertices];
	indices = new GLuint[numIndices];
	unsigned char * data = new unsigned char[numVertices];

	file.read((char *)data, numVertices * sizeof(unsigned char));
	file.close();

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			vertices[offset] = Vector3(
				10*x * HEIGHTMAP_X, /*data[offset] * HEIGHTMAP_Y*/ 1000 * sin(x/10.0), 10*z * HEIGHTMAP_Z);

			textureCoords[offset] = Vector2(
				x * HEIGHTMAP_TEX_X, z * HEIGHTMAP_TEX_Z);

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

	BufferData();

}

void HeightMap::update() {

	for (int x = 0; x < RAW_WIDTH; ++x) {
		for (int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) + z;

			//cout << n.noise(x / 10.0 + current, z / 10.0 + current) << endl;

			vertices[offset] = Vector3(
				10 * x * HEIGHTMAP_X, /*data[offset] * HEIGHTMAP_Y*/ n.noise(x / 50.0 + current, z / 50.0) * 5000.0, 10 * z * HEIGHTMAP_Z);

			textureCoords[offset] = Vector2(
				x * HEIGHTMAP_TEX_X + current, z * HEIGHTMAP_TEX_Z);

		}

	}

	current += PERLIN_STEP;

	BufferData();

}