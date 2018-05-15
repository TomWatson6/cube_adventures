#pragma once
#include <string>
#include <vector>
#include "Input.h"
#include "../game_objects/Cube.h"

using namespace std;

const int NUM_OF_CUBES = 1;

class CubeInput : public Input {

private:
	const string CUBE_1 = "../Data/Levels/cube_1.txt";
	//const string CUBE_SNOW = "Data/Levels/cube_snow.txt";
	//const string CUBE_GRASS = "Data/Levels/cube_grass.txt";
	vector<Cube> cubes;

public:
	CubeInput() {
		cubes.push_back(initialiseCube(CUBE_1, "Level 1"));
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