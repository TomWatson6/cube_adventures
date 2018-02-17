#pragma once
#include <string>
#include <exception>
#include "Map.h"

using namespace std;

class Cube {

public:
	static const int CUBE_SIDES = 6;

	Cube();
	Cube(string name, int dimensions, Map* maps) {

		this->name = name;
		this->dimensions = dimensions;
		
		for (int i = 0; i < CUBE_SIDES; i++) {
			this->maps[i] = maps[i];
		}

	}

	string getName() { return name; }
	int getDimensions() { return dimensions; }
	vector<Map> getMaps() { return maps; }
	Map getMap(int index) { return maps.at(index); }

	void setName(string name) { this->name = name; }
	void setDimensions(int resolution) { this->dimensions = dimensions; }
	void setMaps(vector<Map> maps) { this->maps = maps; }

private:
	
	string name; // Name of the cube to display on screen
	int dimensions; // Amount of tiles on width/height of each map of the cube
	vector<Map> maps; // Maps that are on the cube

};