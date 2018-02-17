#include "CubeInput.h"

Cube CubeInput::initialiseCube(string path, string name) {

	Cube cube = Cube();
	cube.setName(name);

	vector<string> cubeData = readInFromFile(path);

	int dimensions = cubeData.at(0).length();

	vector<Map> maps;

	cube.setDimensions(dimensions);

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {
		Map map = Map();

		map.setIndex(i);
		map.setDimensions(dimensions);

		Tile* tiles = new Tile[dimensions * dimensions]();

		vector<int> tileNumbers;

		for (int j = 0; j < dimensions; j++) {
			for (int k = 0; k < dimensions; k++) {
				tileNumbers.push_back(atoi(cubeData.at(j).substr(j, 1).c_str()));
			}
		}

		for (int j = 0; j < dimensions; j++) {

			for (int k = 0; k < dimensions; k++) {

				int tileNo = tileNumbers.at(j + k * dimensions);

				switch (tileNo) {
				case 0:
					tiles[j + k * dimensions] = Tile(TileType(TileType::COBBLESTONE), 1, 0, 0, 0); // Cobblestone
					break;
				case 1:
					tiles[j + k * dimensions] = Tile(TileType(TileType::LAVA), 0, 1, 20, 0.3); // Lava
					break;
				case 2:
					tiles[j + k * dimensions] = Tile(TileType(TileType::WATER), 0, 1, 0, 0.6); // Water
					break;
				case 3:
					tiles[j + k * dimensions] = Tile(TileType(TileType::TERRAIN_GRASS), 1, 0, 0, 0.8); // Grass
					break;
				case 4:
					tiles[j + k * dimensions] = Tile(TileType(TileType::TERRAIN_SNOW), 1, 0, 0, 0.5); // Snow
					break;
				}

			}

		}

		map.setTiles(tiles);

		maps.push_back(map);

	}

	cube.setMaps(maps);

	return cube;

}