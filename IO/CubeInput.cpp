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

		vector<char> tileNumbers;

		for (int j = 0; j < dimensions; j++) {
			for (int k = 0; k < dimensions; k++) {
				tileNumbers.push_back(*cubeData.at(i * dimensions + j).substr(k, 1).c_str());
			}
		}


		for (int j = 0; j < dimensions; j++) {

			for (int k = 0; k < dimensions; k++) {

				char tileNo = tileNumbers.at(j * dimensions + k);

				switch (tileNo) {
				case '0':
					tiles.push_back(Tile(TileType::LAND)); // Land
					break;
				case '1':
					tiles.push_back(Tile(TileType::WATER)); // Water
					break;
				case '2':
					tiles.push_back(Tile(TileType::START)); // Start
					break;
				case '3':
					tiles.push_back(Tile(TileType::FINISH)); // Finish
					break;
				case '4':
					tiles.push_back(Tile(TileType::INACTIVE)); // Inactive
					break;
				case '5':
					tiles.push_back(Tile(TileType::ACTIVE)); // Active
					break;
				case '6':
					tiles.push_back(Tile(TileType::CONFIRM)); // Confirm
					break;
				case '7':
					tiles.push_back(Tile(TileType::SWAP)); // Swap
					break;
				case '8':
					tiles.push_back(Tile(TileType::RESET)); // Reset
					break;
				case '9':
					tiles.push_back(Tile(TileType::ILLEGAL)); // Illegal
					break;
				case 'A':
					tiles.push_back(Tile(TileType::TELEPORT)); // Teleport
				}

			}

		}

		Map map = Map(i, dimensions, tiles);
		maps.push_back(map);

	}

	cube.setMaps(maps);

	return cube;

}