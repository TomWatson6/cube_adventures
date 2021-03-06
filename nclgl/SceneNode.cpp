
#include "SceneNode.h"

SceneNode::SceneNode(Mesh * mesh, Vector4 colour) {

	if (RenderMap* r = dynamic_cast<RenderMap*>(mesh)) {
		cout << "Render Map" << endl;
		renderMap = r;
		hasRenderMap = true;
	}
	else {
		cout << "Cube" << endl;
		this->mesh = mesh;
		hasMesh = true;
	}

	this->colour = colour;
	boundingRadius = 1.0f;
	distanceFromCamera = 0.0f;
	parent = NULL;
	modelScale = Vector3(1, 1, 1);

}

SceneNode::~SceneNode(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];

	}

}

void SceneNode::AddChild(SceneNode * s) {
	children.push_back(s);
	s->parent = this;

}
void SceneNode::Draw(const OGLRenderer & r) {
	if (hasMesh) { mesh->Draw(); }
	if (hasRenderMap) { renderMap->Draw(); }

}

void SceneNode::Update(float msec) {
	if (parent) { // This node has a parent ...
		worldTransform = parent->worldTransform * transform;
	}
	else { // Root node , world transform is local transform !
		worldTransform = transform;
	}
	for (vector < SceneNode * >::iterator i = children.begin();
		i != children.end(); ++i) {
		(*i)->Update(msec);
	}

	if (hasRenderMap) { renderMap->update(); }

}
