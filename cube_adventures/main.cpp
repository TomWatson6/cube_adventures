#include "../nclgl/window.h"
#include "../nclgl/Renderer.h"
#include "../IO/CubeInput.h"
#include "../Entities/Player.h"
#include "../Physics/Physics.h"
#include "../Sound/Sound.h"

#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "IO.lib")
#pragma comment(lib, "game_objects.lib")
#pragma comment(lib, "Entities.lib")
#pragma comment(lib, "Physics.lib")
#pragma comment(lib, "Sound.lib")

static const float PULSE_MAGNITUDE = 120.0 / 255.0;

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

	float cubeLength = (RAW_WIDTH - 1) * HEIGHTMAP_X * 10;

	float xPos = ((m.getStartTile() % m.getDimensions()) * sideLength) - (0.5 * cubeLength) + (0.5 * sideLength);
	float yPos = 0.5 * cubeLength - 0.5 * sideLength - (m.getStartTile() / m.getDimensions()) * sideLength;
	//float xPos = (m.getStartTile() % m.getDimensions()) * sideLength + 0.5 * sideLength - (5 * RAW_WIDTH * HEIGHTMAP_X - 5 * HEIGHTMAP_X);
	//float yPos = (5 * RAW_HEIGHT * HEIGHTMAP_Z - 5 * HEIGHTMAP_Z) - ((m.getStartTile() / m.getDimensions()) * sideLength - 0.5 * sideLength);
	float zPos = 0.5 * cubeLength;

	cout << xPos << endl;
	cout << m.getStartTile() << endl;
	cout << m.getDimensions() << endl;
	cout << sideLength << endl;

	return Player(xPos, yPos, zPos, sideLength, startTile);

}

int main() {

	Physics physics = Physics();

	bool fadingOut = false;
	bool fadingIn = false;

	float progress = 0;

	int currentCube = 0;
	int currentMap = 0;
	bool complete = false;

	Window w("Cube Adventures!", 1280, 800, false);

	if (!w.HasInitialised()) {
		return -1;
	}

	int frameCount = 0;
	int secondsPassed = 1;
	float currentTime = w.GetTimer()->GetTimedMS();

	CubeInput cubeInput = CubeInput();

	vector<Cube> cubes = cubeInput.getCubes();

	/*for (Cube cube : cubes) {
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
	}*/

	

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}
	
	float dimensions = renderer.getMap(currentMap).getDimensions();
	float sideLength = 10.0 * (RAW_WIDTH - dimensions / 4.0) * HEIGHTMAP_X / dimensions;

	Player player = initialisePlayer(cubes.at(currentCube).getMap(currentMap), renderer.getGroundLevel(), sideLength, cubes.at(currentCube).getMap(currentMap).getStartTile());

	RenderMap* renderMap = renderer.getRenderMap(currentMap);

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	Sound sound = Sound();

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		//Game Stuff goes here

		//ORDERING MAY NEED TO BE CHANGED

		//Is player at the end square? - if so update level
		//Has player touched interactive tile? - if so update colour of tile

		//Is player/cube map moving? - if not check for input
		//KeyboardInput::CheckForInput();

		if (!player.getIsMoving()) {
			if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::UP)) { 
					player.move(Direction::UP, cubes.at(currentCube).getMap(currentMap).getDimensions()); 
				}
			}
			else if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::LEFT)) { 
					player.move(Direction::LEFT, cubes.at(currentCube).getMap(currentMap).getDimensions()); 
				}
			}
			else if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::DOWN)) { 
					player.move(Direction::DOWN, cubes.at(currentCube).getMap(currentMap).getDimensions()); 
				}
			}
			else if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
				if (physics.validMove(player, cubes.at(currentCube).getMap(currentMap), Direction::RIGHT)) { 
					player.move(Direction::RIGHT, cubes.at(currentCube).getMap(currentMap).getDimensions()); 
				}
			}
		}

		player.update(sound);
		renderer.updatePlayer(player.getPosx(), player.getPosy(), player.getPosz(), sideLength, player.getProgress(), player.getDirection());

		//cout << !renderer.getMap(currentMap).isComplete() << endl;

		

		if (player.getTriggerPulse() && !complete) {
			player.setTriggerPulse(false);
			TileType type = renderer.getMap(currentMap).getTile(player.getCurrentTile()).getType();

			if (type == TileType::INACTIVE || type == TileType::ACTIVE) {
				sound.playInteractiveTileSound();
				if (type == TileType::INACTIVE) {
					renderMap->negateTile(player.getCurrentTile());
					renderer.getRenderMap(currentMap)->pulse(player.getCurrentTile(), PULSE_MAGNITUDE);
				}
				else if (type == TileType::ACTIVE) {
					//renderMap->negateTile(player.getCurrentTile());
					//Reset all tiles
					for (int i = 0; i < dimensions * dimensions; i++) {
						if (renderMap->getTile(i).getType() == TileType::ACTIVE) {
							renderMap->negateTile(i);
							renderMap->pulse(i, PULSE_MAGNITUDE);
						}
					}
					fadingOut = true;
				}
				
			}
			else if (type == TileType::SWAP || type == TileType::RESET || type == TileType::CONFIRM) {

				if (type == TileType::SWAP) {
					sound.playSwapSound();
					for (int i = 0; i < dimensions * dimensions; i++) {
						if (renderMap->getTile(i).getType() == TileType::INACTIVE) {
							renderMap->negateTile(i);
							renderMap->pulse(i, PULSE_MAGNITUDE);
						}
						else if (renderMap->getTile(i).getType() == TileType::ACTIVE) {
							renderMap->negateTile(i);
							renderMap->pulse(i, PULSE_MAGNITUDE);
						}
					}

				}
				else if (type == TileType::RESET) {
			
					for (int i = 0; i < dimensions * dimensions; i++) {
						if (renderMap->getTile(i).getType() == TileType::ACTIVE) {
							renderMap->negateTile(i);
							renderMap->pulse(i, PULSE_MAGNITUDE);
						}
					}

				}
				else if (type == TileType::CONFIRM) {
					
					bool correct = true;

					for (int i = 0; i < dimensions * dimensions; i++) {
						if (renderMap->getTile(i).getType() == TileType::INACTIVE) {
							correct = false;
						}
					}

					if (correct) {

						sound.playConfirmSound();

						complete = true;
						renderMap->reduceBaseColours();
						renderMap->colourFinishTile();

						int tileIndex;

						for (int i = 0; i < dimensions * dimensions; i++) {
							if (renderMap->getMap().getTile(i).getType() == TileType::FINISH) {
								tileIndex = i;
								break;
							}
						}

						renderMap->pulse(tileIndex, PULSE_MAGNITUDE * 2);

					}

				}

				if (fadingOut) {
					renderer.getPlayer()->GetMesh()->updateAlpha(-ALPHA_STEP * currentTime / 1000.0);
				}
				if (renderer.getPlayer()->GetMesh()->getAlpha() <= 0 && fadingOut) {
					renderer.getPlayer()->GetMesh()->setAlpha(0);
					fadingOut = false;
					if (mapTransition) {
						if (currentMap == Cube::CUBE_SIDES - 1) {
							cubeTransition = true;
							mapTransition = false;
							currentMap = 0;
							currentCube++;
						}
						else {
							currentMap++;
						}

					}
					else {
						fadingIn = true;
					}
				}

				//Todo -- Set Cube transform to needed one before the rotation is carried out (currentMap - 1) if mapTransition
				// (currentMap) if cubeTransition

				if (mapTransition || cubeTransition) {

					if (cubeTransition) {
						//work out some algorithm to make the cube transition look cool
						if (progress == PROGRESS_MAX) {
							cubeTransition = false;

							player = initialisePlayer(cubes.at(currentCube).getMap(currentMap), renderer.getGroundLevel(), sideLength, cubes.at(currentCube).getMap(currentMap).getStartTile());
							renderer.updatePlayer(player.getPosx(), player.getPosy(), player.getPosz(), sideLength, player.getProgress(), player.getDirection());
							// ??? fadingIn = true;
						}
					}
					else if (mapTransition) {
						switch (currentMap) {
						case 0:
							renderer.getRoot().setTransform(renderer.getRoot().getWorldTransform() *
								Matrix4::Rotation(progress, Vector3(1, 0, 0)));
							break;
						case 1:
							renderer.getRoot().setTransform(renderer.getRoot().getWorldTransform() *
								Matrix4::Rotation(progress, Vector3(0, 0, 1)));
							break;
						case 2:
							renderer.getRoot().setTransform(renderer.getRoot().getWorldTransform() *
								Matrix4::Rotation(-progress, Vector3(0, 1, 0)));
							break;
						case 3:
							renderer.getRoot().setTransform(renderer.getRoot().getWorldTransform() *
								Matrix4::Rotation(progress, Vector3(1, 0, 0)));
							break;
						case 4:
							renderer.getRoot().setTransform(renderer.getRoot().getWorldTransform() *
								Matrix4::Rotation(progress, Vector3(0, 0, 1)));
						}
						progress++;
						if (progress >= PROGRESS_MAX) {
							progress = 0;
							mapTransition = false;

							//renderer.getRoot().setTransform() -- Set to correct rotation for current map
						}
					}

				}
				if (fadingIn) {
					renderer.getPlayer()->GetMesh()->updateAlpha(ALPHA_STEP * currentTime / 1000.0);
				}
				if (renderer.getPlayer()->GetMesh()->getAlpha() >= 1) {
					renderer.getPlayer()->GetMesh()->setAlpha(1);
					fadingIn = false;
				}

			}
		}

		//Update player in the renderer
		//renderer.updatePlayerPos(); -- To be implemented

		//if(!player.getIsMoving() && player.getCurrentTile() == cubes.at(currentCube).getMap(currentMap).getEndtile()) {
		//nextLevel(); -- To be implemented
		//}

		//Note -- nextLevel() or isMoving being true will make a bool inputAllowed = false, and true when they are false

		//Note -- positive y is up and tile array goes across and down, change logic accordingly (validMove() is one to change)

		renderer.UpdateScene(currentTime);
		renderer.RenderScene();
		
		currentTime = w.GetTimer()->GetTimedMS();

		if (currentTime < secondsPassed * 1000.0f) {
			frameCount++;
			cout << 1000.0f / currentTime << endl;
		}
		else {
			cout << "Frames Per Second: " << frameCount << endl;
			frameCount = 0;
			secondsPassed++;
		}

	}

	return 0;

}

