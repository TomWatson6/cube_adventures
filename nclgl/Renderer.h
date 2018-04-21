# pragma once

# include "OGLRenderer.h"
# include "camera.h"
# include "RenderMap.h"
# include "SceneNode.h"
# include "../Entities/Player.h"
# include "../IO/CubeInput.h"
# include "PerlinNoise.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	float getGroundLevel() { return groundLevel.z; }

	void updatePlayer(float posx, float posy, float posz, float sideLength, float progress, Direction dir);

protected:

	float halfSideLength = (10 * (RAW_WIDTH - 1) * HEIGHTMAP_X) / 2;

	Vector3 cubePosition = Vector3(0, 0, -3.5 * halfSideLength);
	Vector3 groundLevel = Vector3(0, 0, -2.5 * halfSideLength);

	SceneNode* root;
	SceneNode* cubeSides;
	SceneNode* player;
	Camera * camera;

	float dimensions;
	float* tileInfo;
	float* currentTileInfo;

	int counter = 1;

	float scale = 0;
	float rotation = 0;
	Vector3 position = Vector3(0, 0, 0);

};