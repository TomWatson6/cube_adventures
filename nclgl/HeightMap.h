# pragma once

# include <string>
# include <iostream>
# include <fstream>
# include "mesh.h"
# include "PerlinNoise.h"

# define RAW_WIDTH 90
# define RAW_HEIGHT 90

# define HEIGHTMAP_X 16.0f
# define HEIGHTMAP_Z 16.0f
# define HEIGHTMAP_Y 1.25f
# define HEIGHTMAP_TEX_X 1.0f / 16.0f
# define HEIGHTMAP_TEX_Z 1.0f / 16.0f

class HeightMap : public Mesh {
public:
	HeightMap() {};
	HeightMap(std::string name);
	~HeightMap(void) {};
	
	virtual void update();
	int t;
	float current = 0;
	Vector2* Gradient = new Vector2[RAW_WIDTH * RAW_HEIGHT]();

protected:
	const float PERLIN_STEP = 0.0035;
	PerlinNoise n = PerlinNoise();

};
