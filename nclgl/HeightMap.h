# pragma once

# include <string>
# include <iostream>
# include <fstream>
# include "mesh.h"

# define RAW_WIDTH 50
# define RAW_HEIGHT 50

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
	int t;
	Vector2* Gradient = new Vector2[RAW_WIDTH * RAW_HEIGHT]();

};
