#include "../nclgl/window.h"
#include "../nclgl/Renderer.h"
#include "../IO/CubeInput.h"
#include "../Entities/Player.h"
#include "../Physics/Physics.h"

#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "IO.lib")
#pragma comment(lib, "game_objects.lib")
#pragma comment(lib, "Entities.lib")
#pragma comment(lib, "Physics.lib")

Player initialisePlayer(Map m, float groundLevel, float sideLength, int startTile) {

	//Calculate appropriate position of the starting tile

	//Initialise Player
	//Player player = Player(
	//xPos of starting tile + half tileLength - half map side length
	//yPos of starting tile + half tileLength - half map side length
	//ground level + half tileLength
	//tileLength
	//cubes.at(currentCube).getMap(currentMap).getStartingTile() -- going to have to adapt IO for this to happen - make manual for testing
	//);

	float xPos = (m.getStartTile() % m.getDimensions()) * sideLength + 0.5 * sideLength - 5 * RAW_WIDTH * HEIGHTMAP_X;
	float yPos = (m.getStartTile() / m.getDimensions()) * sideLength - 0.5 * sideLength + 5 * RAW_HEIGHT * HEIGHTMAP_Z;
	float zPos = 5 * RAW_HEIGHT * HEIGHTMAP_Z + 0.5 * sideLength;

	cout << xPos << endl;
	cout << m.getStartTile() << endl;

	return Player(xPos, yPos, zPos, sideLength, startTile);

}

int main() {

	Physics physics = Physics();

	int currentCube = 0;
	int currentMap = 0;

	Window w("Cube Adventures!", 1280, 800, false);

	if (!w.HasInitialised()) {
		return -1;
	}

	CubeInput cubeInput = CubeInput();

	vector<Cube> cubes = cubeInput.getCubes();

	for (Cube cube : cubes) {
		for (Map map : cube.getMaps()) {
			for (int i = 0; i < map.getDimensions(); i++) {
				for (int j = 0; j < map.getDimensions(); j++) {
					if (map.getTile(i + j * map.getDimensions()).getType() == TileType::LAND) {
						cout << "0 ";
					}
					else if (map.getTile(i + j * map.getDimensions()).getType() == TileType::WATER) {
						cout << "1 ";
					}
					else if (map.getTile(i + j * map.getDimensions()).getType() == TileType::INTERACTIVE) {
						cout << "2 ";
					}
					else if (map.getTile(i + j * map.getDimensions()).getType() == TileType::START) {
						cout << "3 ";
					}
					else {
						cout << "4 ";
					}
				}
			}
		}
	}

	

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	float sideLength = (10 * HEIGHTMAP_X * RAW_WIDTH) / cubes.at(currentCube).getMap(currentMap).getDimensions();

	Player player = initialisePlayer(cubes.at(currentCube).getMap(currentMap), renderer.getGroundLevel(), sideLength, cubes.at(currentCube).getMap(currentMap).getStartTile());

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		//Game Stuff goes here

		//ORDERING MAY NEED TO BE CHANGED

		//Is player at the end square? - if so update level
		//Has player touched interactive tile? - if so update colour of tile

		//Is player/cube map moving? - if not check for input
		//KeyboardInput::CheckForInput();

		if (!player.getIsMoving()) {
			if (!Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::UP)) { player.move(Direction::UP); }
			}
			else if (!Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::LEFT)) { player.move(Direction::LEFT); }
			}
			else if (!Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::DOWN)) { player.move(Direction::DOWN); }
			}
			else if (!Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::RIGHT)) { player.move(Direction::RIGHT); }
			}
		}

		player.update();
		renderer.updatePlayer(player.getPosx(), player.getPosy(), player.getPosz(), sideLength, player.getProgress(), player.getDirection());

		//Update player in the renderer
		//renderer.updatePlayerPos(); -- To be implemented

		//if(!player.getIsMoving() && player.getCurrentTile() == cubes.at(currentCube).getMap(currentMap).getEndtile()) {
		//nextLevel(); -- To be implemented
		//}

		//Note -- nextLevel() or isMoving being true will make a bool inputAllowed = false, and true when they are false

		//Note -- positive y is up and tile array goes across and down, change logic accordingly (validMove() is one to change)


		renderer.UpdateScene(w.GetTimer()->GetTimedMS());
		renderer.RenderScene();
	}

	return 0;

}

