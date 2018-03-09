#include "MapNode.h"

MapNode::MapNode(RenderMap* renderMap, Vector4 colour) {

	this->renderMap = renderMap;
	this->colour = colour;
	boundingRadius = 1.0f;
	distanceFromCamera = 0.0f;
	parent = NULL;
	modelScale = Vector3(1, 1, 1);

}

void MapNode::Draw(const OGLRenderer & r) {

	if (renderMap) { renderMap->Draw(); };

}