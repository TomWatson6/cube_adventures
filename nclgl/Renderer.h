# pragma once

# include "OGLRenderer.h"
# include "camera.h"
# include "RenderMap.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	RenderMap* renderMap;
	Camera * camera;

	float dimensions;
	float* tileInfo;

	int counter = 1;

};