# pragma once

# include <string>
# include <iostream>
# include <fstream>
# include "mesh.h"

# define RAW_WIDTH 257
# define RAW_HEIGHT 257

# define HEIGHTMAP_X 16.0f
# define HEIGHTMAP_Z 16.0f
# define HEIGHTMAP_Y 1.25f
# define HEIGHTMAP_TEX_X 1.0f / 16.0f
# define HEIGHTMAP_TEX_Z 1.0f / 16.0f
class HeightMap : public Mesh {
public:
	HeightMap(std::string name);
	~HeightMap(void) {};
	
	void update();
	float perlinNoise(float x, float y);
	void initialiseGradient();
	float dotGridGradient(int ix, int iy, float x, float y);

	int t;
	Vector2* Gradient = new Vector2[RAW_WIDTH * RAW_HEIGHT]();

};
