#pragma once
#include <string>
#include <vector>
#include "Input.h"
#include "../cube_adventures/Cube.h"

using namespace std;

class CubeInput : public Input {

private:
	const string CUBE_LAVA = "../Data/Levels/cube_lava.txt";
	//const string CUBE_SNOW = "Data/Levels/cube_snow.txt";
	//const string CUBE_GRASS = "Data/Levels/cube_grass.txt";
	vector<Cube> cubes;

public:
	CubeInput() {
		cubes.push_back(initialiseCube(CUBE_LAVA, "Lava"));
		//cubes.push_back(initialiseCube(CUBE_SNOW, "Snow"));
		//cubes.push_back(initialiseCube(CUBE_GRASS, "Grass"));
	}

	Cube getCube(int index) {
		return cubes.at(index);
	}

	vector<Cube> getCubes() {
		return cubes;
	}

	Cube initialiseCube(string path, string name);

};