#include "CubeInput.h"

Cube CubeInput::initialiseCube(string path, string name) {

	Cube cube = Cube();
	cube.setName(name);

	vector<string> cubeData = readInFromFile(path);

	int dimensions = cubeData.at(0).length();

	vector<Map> maps;

	cube.setDimensions(dimensions);

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		vector<Tile> tiles;

		vector<int> tileNumbers;

		for (int j = 0; j < dimensions; j++) {
			for (int k = 0; k < dimensions; k++) {
				tileNumbers.push_back(atoi(cubeData.at(j).substr(k, 1).c_str()));
			}
		}

		for (int j = 0; j < dimensions; j++) {

			for (int k = 0; k < dimensions; k++) {

				int tileNo = tileNumbers.at(j + k * dimensions);

				switch (tileNo) {
				case 0:
					tiles.push_back(Tile(TileType::LAND)); // Land
					break;
				case 1:
					tiles.push_back(Tile(TileType::WATER)); // Water
					break;
				case 2:
					tiles.push_back(Tile(TileType::INTERACTIVE)); // Interactive
					break;
				case 3:
					tiles.push_back(Tile(TileType::START)); // Start
					break;
				case 4:
					tiles.push_back(Tile(TileType::FINISH)); // Finish
				}

			}

		}

		Map map = Map(i, dimensions, tiles);
		maps.push_back(map);

	}

	cube.setMaps(maps);

	return cube;

}