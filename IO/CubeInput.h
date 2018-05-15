#pragma once
#include <string>
#include <vector>
#include "Input.h"
#include "../game_objects/Cube.h"

using namespace std;

const int NUM_OF_CUBES = 2;

class CubeInput : public Input {

private:
	const string CUBE_1 = "../Data/Levels/cube_1.txt";
	const string CUBE_2 = "../Data/Levels/cube_2.txt";
	
	vector<Cube> cubes;

public:
	CubeInput() {
		cubes.push_back(initialiseCube(CUBE_1, "Level 1"));
		cubes.push_back(initialiseCube(CUBE_2, "Level 2"));
	}

	Cube getCube(int index) {
		return cubes.at(index);
	}

	vector<Cube> getCubes() {
		return cubes;
	}

	Cube initialiseCube(string path, string name);

};