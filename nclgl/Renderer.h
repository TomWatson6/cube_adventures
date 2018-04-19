# pragma once

# include "OGLRenderer.h"
# include "camera.h"
# include "RenderMap.h"
# include "SceneNode.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:

	float halfSideLength = (10 * RAW_WIDTH * HEIGHTMAP_X - 10 * HEIGHTMAP_X) / 2;

	Vector3 cubePosition = Vector3(0, 0, -3.5 * halfSideLength);
	Vector3 groundLevel = Vector3(0, 0, -2.5 * halfSideLength);

	SceneNode* root;
	SceneNode* cubeSides;
	Camera * camera;

	float dimensions;
	float* tileInfo;

	int counter = 1;

	float scale = 0;
	float rotation = 0;
	Vector3 position = Vector3(0, 0, 0);

};