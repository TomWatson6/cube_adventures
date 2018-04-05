#pragma once
# include "SceneNode.h"

class MapNode : public SceneNode {

public:
	MapNode() {};
	MapNode(RenderMap* renderMap, Vector4 colour);

	void Draw(const OGLRenderer & r);

};