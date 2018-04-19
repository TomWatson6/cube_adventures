#include "../nclgl/window.h"
#include "../nclgl/Renderer.h"
#include "../IO/CubeInput.h"
#include "../entities/Player.h"
#include "../Physics/Physics.h"

#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "IO.lib")
#pragma comment(lib, "game_objects.lib")

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
					if (map.getTile(i + j * map.getDimensions()).getType() == TileType::COBBLESTONE) {
						cout << "0 ";
					}
					else if (map.getTile(i + j * map.getDimensions()).getType() == TileType::LAVA) {
						cout << "1 ";
					}
					else if (map.getTile(i + j * map.getDimensions()).getType() == TileType::WATER) {
						cout << "2 ";
					}
					else if (map.getTile(i + j * map.getDimensions()).getType() == TileType::TERRAIN_GRASS) {
						cout << "3 ";
					}
					else {
						cout << "4 ";
					}
				}
			}
		}
	}

	//Initialise Player
	//Player player = Player(
	//xPos of starting tile + half tileLength - half map side length
	//yPos of starting tile + half tileLength - half map side length
	//ground level + half tileLength
	//tileLength
	//cubes.at(currentCube).getMap(currentMap).getStartingTile() -- going to have to adapt IO for this to happen - make manual for testing
	//);

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	//renderer.setPlayer(); -- To be implemented

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		//Game Stuff goes here

		//ORDERING MAY NEED TO BE CHANGED

		//Is player at the end square? - if so update level
		//Has player touched interactive tile? - if so update colour of tile

		//Is player/cube map moving? - if not check for input
		//KeyboardInput::CheckForInput();

		if (!Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			//if(physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::UP) { player.move(Direction::UP); }
		}
		else if (!Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {

		}
		else if (!Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {

		}
		else if (!Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {

		}

		//Update player in the renderer
		//renderer.updatePlayerPos(player.getPosx(), player.getPosy(), player.getPosz(), player.getProgress(), player.getDirection()); -- To be implemented

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