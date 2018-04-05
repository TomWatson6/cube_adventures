#include "../nclgl/window.h"
#include "../nclgl/Renderer.h"
#include "../IO/CubeInput.h"

#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "IO.lib")
#pragma comment(lib, "game_objects.lib")

int main() {

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

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);


	// Game stuff goes here!


	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.UpdateScene(w.GetTimer()->GetTimedMS());
		renderer.RenderScene();
	}

	delete &renderer;
	delete &w;
	delete &cubeInput;

	return 0;

}