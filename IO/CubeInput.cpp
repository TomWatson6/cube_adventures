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
					tiles.push_back(Tile(TileType(TileType::COBBLESTONE), 1, 0, 0, 0)); // Cobblestone
					break;
				case 1:
					tiles.push_back(Tile(TileType(TileType::LAVA), 0, 1, 20, 0.3)); // Lava
					break;
				case 2:
					tiles.push_back(Tile(TileType(TileType::WATER), 0, 1, 0, 0.6)); // Water
					break;
				case 3:
					tiles.push_back(Tile(TileType(TileType::TERRAIN_GRASS), 1, 0, 0, 0.8)); // Grass
					break;
				case 4:
					tiles.push_back(Tile(TileType(TileType::TERRAIN_SNOW), 1, 0, 0, 0.5)); // Snow
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