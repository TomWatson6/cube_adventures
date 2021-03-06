#include "Renderer.h"
#include <iostream>

using namespace std;

Renderer::Renderer(Window & parent, int currentCube) : OGLRenderer(parent) {

	//Initialise map rotations
	mapRotations[0] = Matrix4();
	mapRotations[1] = mapRotations[0] * Matrix4::Rotation(-90.0f, Vector3(1, 0, 0));
	mapRotations[2] = mapRotations[1] * Matrix4::Rotation(90.0f, Vector3(0, 1, 0));
	mapRotations[3] = mapRotations[2] * Matrix4::Rotation(-90.0f, Vector3(1, 0, 0));
	mapRotations[4] = mapRotations[3] * Matrix4::Rotation(90.0f, Vector3(0, 1, 0));
	mapRotations[5] = mapRotations[4] * Matrix4::Rotation(-90.0f, Vector3(1, 0, 0));

	camera = new Camera();
	counter = 0;

	currentShader = new Shader("../Shaders/TexturedVertex.glsl",
		"../Shaders/TexturedFragment.glsl", 
		"../Shaders/LightGeom.glsl");

	light = new Light(Vector3((RAW_HEIGHT * HEIGHTMAP_X * -5.0f),
		RAW_HEIGHT * HEIGHTMAP_Z * 5.0f, (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f)),
		Vector4(1, 1, 1, 1), (RAW_WIDTH * HEIGHTMAP_X) * 10.0f * 10.0f);

	if (!currentShader->LinkProgram()) {
		return;

	}

	projMatrix = Matrix4::Perspective(1.0f, 1000000.0f,
		(float)width / (float)height, 45.0f);

	cubeSides = new SceneNode[Cube::CUBE_SIDES];

	/*GLuint texture = SOIL_load_OGL_texture(
		"../Textures/water_texture.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);*/

	
	//currentTileInfo = new float[dimensions * dimensions * 2];
	//tileInfo = new float[Cube::CUBE_SIDES * dimensions * dimensions * 2];

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		Map map = cubeInput.getCube(currentCube).getMap(i);

		RenderMap* renderMap = new RenderMap(i, map, MapType::WALKABLE, "../Textures/terrain.raw");

		//renderMap->SetTexture(texture);

		/*if (!renderMap->GetTexture()) {
			return;
		}*/

		//SetTextureRepeating(renderMap->GetTexture(), true);
		//SetTextureRepeating(renderMap->cobblestoneTexture, true);

		dimensions = renderMap->getDimensions();

		tileInfo = new float[dimensions * dimensions];

		for (int j = 0; j < dimensions * dimensions; j++) {

			switch (renderMap->getTile(j).getType()) {
			case TileType::LAND:
				tileInfo[j] = 0;
				break;
			case TileType::WATER:
				tileInfo[j] = 1;
				break;
			case TileType::START:
				tileInfo[j] = 2;
				break;
			case TileType::FINISH:
				tileInfo[j] = 3;
				break;
			case TileType::INACTIVE:
				tileInfo[j] = 4;
				break;
			case TileType::ACTIVE:
				tileInfo[j] = 5;
				break;
			case TileType::CONFIRM:
				tileInfo[j] = 6;
				break;
			case TileType::SWAP:
				tileInfo[j] = 7;
			}

		}

		/*for (int i = 0; i < dimensions * dimensions * 2; i++) {
			cout << tileInfo[i];
		}
		cout << endl;*/

		Vector4 colour = Vector4(1, 1, 1, 1);

		cubeSides[i] = SceneNode(renderMap, colour);

		cout << cubeSides[i].GetRenderMap()->getIndex() << endl;

		//cubeSides[i]->SetModelScale(Vector3(i / 6, i / 6, i / 6));

	}

	root = new SceneNode();

	playerRoot = new SceneNode();

	root->AddChild(playerRoot);

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {
		root->AddChild(&cubeSides[i]);
	}

	player = new SceneNode();
	player->SetMesh(Mesh::LoadMeshFile("../Meshes/cube.asciimesh"));

	playerRoot->AddChild(player);

	Matrix4 transformation;

	root->SetTransform(Matrix4::Translation(cubePosition));

	transformation = Matrix4::Translation(Vector3(-halfSideLength, halfSideLength, halfSideLength));
	transformation = transformation * Matrix4::Rotation(-90.0f, Vector3(0, 0, 1));
	transformation = transformation * Matrix4::Rotation(-90.0f, Vector3(1, 0, 0));

	cubeSides[0].SetTransform(transformation);

	transformation = Matrix4::Translation(Vector3(-halfSideLength, halfSideLength, -halfSideLength));
	transformation = transformation * Matrix4::Rotation(-90.0f, Vector3(0, 1, 0));
	transformation = transformation * Matrix4::Rotation(180.0f, Vector3(1, 0, 0));

	cubeSides[1].SetTransform(transformation);

	transformation = Matrix4::Translation(Vector3(halfSideLength, halfSideLength, -halfSideLength));
	transformation = transformation * Matrix4::Rotation(-90.0f, Vector3(0, 1, 0));
	transformation = transformation * Matrix4::Rotation(90.0f, Vector3(1, 0, 0));

	cubeSides[2].SetTransform(transformation);

	transformation = Matrix4::Translation(Vector3(-halfSideLength, halfSideLength, -halfSideLength));
	transformation = transformation * Matrix4::Rotation(90.0f, Vector3(1, 0, 0));

	cubeSides[3].SetTransform(transformation);

	transformation = Matrix4::Translation(Vector3(-halfSideLength, -halfSideLength, -halfSideLength));
	//transformation = transformation * Matrix4::Rotation(180.0f, Vector3(1, 0, 0));

	cubeSides[4].SetTransform(transformation);

	transformation = Matrix4::Translation(Vector3(-halfSideLength, halfSideLength, -halfSideLength));
	//transformation = transformation * Matrix4::Rotation(180.0f, Vector3(0, 1, 0));
	transformation = transformation * Matrix4::Rotation(-90.0f, Vector3(0, 0, 1));

	cubeSides[5].SetTransform(transformation);

	/*Matrix4 transform1 = Matrix4::Rotation(90.0f, Vector3(1, 0, 0));
	Matrix4 transform2 = Matrix4::Translation(Vector3(0, 0, 1));
	Matrix4 transform3 = Matrix4::Translation(Vector3(1, 0, 0));
	Matrix4 transform4 = Matrix4::Rotation(90.0f, Vector3(0, 0, 1));

	Matrix4 modelMatrix;

	for (int i = 0; i < Cube::CUBE_SIDES / 2; i++) {

	modelMatrix = transform1 * transform2;

	cubeSides[i * 2]->SetTransform(cubeSides[i * 2]->GetWorldTransform() * modelMatrix);

	modelMatrix = modelMatrix * transform3 * transform4;

	cubeSides[i * 2 + 1]->SetTransform(cubeSides[i * 2 + 1]->GetWorldTransform() * modelMatrix);

	}*/

	/*Map map = cubeInput.getCube(0).getMap(0);

	renderMap = new RenderMap(0, map, "../Textures/terrain.raw");*/



	/*for (int i = 0; i < dimensions * dimensions * 2; i++) {
	cout << tileInfo[i];
	}
	cout << endl;*/

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	init = true;

}

Renderer ::~Renderer(void) {

	delete camera;
	delete[] tileInfo;
	delete[] cubeSides;
	delete light;
	//delete root;

}

void Renderer::setPlayerRootRotation(int currentMap) {

	playerRoot->SetTransform(mapRotations[currentMap]);

}

void Renderer::updateCubeSides(int currentCube) {

	//Reset root position and rotation
	root->SetTransform(Matrix4::Translation(cubePosition));
	playerRoot->SetTransform(Matrix4());

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		Map map = cubeInput.getCube(currentCube).getMap(i);

		RenderMap* renderMap = new RenderMap(i, map, MapType::WALKABLE, "../Textures/terrain.raw");

		dimensions = renderMap->getDimensions();

		cubeSides[i].setRenderMap(renderMap);

	}

}

void Renderer::updatePlayer(float posx, float posy, float posz, float sideLength, float progress, Direction dir) {

	Matrix4 translation = Matrix4::Translation(Vector3(posx, posy, posz));
	Matrix4 scale = Matrix4::Scale(Vector3(sideLength / 2, sideLength / 2, sideLength / 2));
	Matrix4 rotation;

	if (dir == Direction::LEFT) {
		rotation = Matrix4::Rotation(-progress, Vector3(0, 1, 0));
	}
	else if (dir == Direction::RIGHT) {
		rotation = Matrix4::Rotation(progress, Vector3(0, 1, 0));
	}
	else if (dir == Direction::UP) {
		rotation = Matrix4::Rotation(-progress, Vector3(1, 0, 0));
	}
	else if (dir == Direction::DOWN) {
		rotation = Matrix4::Rotation(progress, Vector3(1, 0, 0));
	}

	player->SetTransform(translation * rotation *  scale);

}

void Renderer::UpdateScene(float msec) {
	//camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();

	root->Update(msec);
	//player->Update(msec);

}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());

	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(),
		"cameraPos"), 1, (float*)&camera->GetPosition());

	UpdateShaderMatrices();
	SetShaderLight(*light);

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(),
			"modelMatrix"), 1, false, (float*)&cubeSides[i].GetWorldTransform());

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"currentMap"), i);

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"tileLength"), cubeSides[i].GetRenderMap()->getTileLength());

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"dimensions"), dimensions);

		glUniform1fv(glGetUniformLocation(currentShader->GetProgram(),
			"tileInfo"), dimensions * dimensions, (const GLfloat*)tileInfo);

		cubeSides[i].Draw(*this);

	}

	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(),
		"modelMatrix"), 1, false, (float*)&player->GetWorldTransform());

	player->Draw(*this);

	glUseProgram(0);
	SwapBuffers();

}
