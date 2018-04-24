#include "Renderer.h"
#include <iostream>

using namespace std;

Renderer::Renderer(Window & parent) : OGLRenderer(parent) {

	camera = new Camera();
	counter = 0;

	currentShader = new Shader("../Shaders/TexturedVertex.glsl",
		"../Shaders/TexturedFragment.glsl");

	if (!currentShader->LinkProgram()) {
		return;

	}

	projMatrix = Matrix4::Perspective(1.0f, 1000000.0f,
		(float)width / (float)height, 45.0f);

	CubeInput cubeInput = CubeInput();

	cubeSides = new SceneNode[Cube::CUBE_SIDES];

	GLuint texture = SOIL_load_OGL_texture(
		"../Textures/water_texture.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	
	//currentTileInfo = new float[dimensions * dimensions * 2];
	//tileInfo = new float[Cube::CUBE_SIDES * dimensions * dimensions * 2];

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		Map map = cubeInput.getCube(0).getMap(i);

		RenderMap* renderMap = new RenderMap(i, map, MapType::WALKABLE, "../Textures/terrain.raw");

		renderMap->SetTexture(texture);

		if (!renderMap->GetTexture()) {
			return;
		}

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

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {
		root->AddChild(&cubeSides[i]);
	}

	player = new SceneNode();
	player->SetMesh(Mesh::LoadMeshFile("../Meshes/cube.asciimesh"));

	root->AddChild(player);

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
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	init = true;

}
Renderer ::~Renderer(void) {

	delete camera;
	delete[] tileInfo;
	delete[] cubeSides;
	//delete root;

}

void Renderer::updatePlayer(float posx, float posy, float posz, float sideLength, float progress, Direction dir) {

	//Matrix4 translation = root->GetWorldTransform();
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
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();

	root->Update(msec);
	player->Update(msec);

	/*for (int i = 0; i < Cube::CUBE_SIDES; i++) {
	cubeSides[i].Update(msec);
	}*/

}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		/*for (int j = 0; j < dimensions * dimensions; j++) {
			int index = i * dimensions * dimensions * 2 + j * 2;
			currentTileInfo[j * 2] = tileInfo[index];
			currentTileInfo[j * 2 + 1] = tileInfo[index + 1];
		}*/

		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(),
			"modelMatrix"), 1, false, (float*)&cubeSides[i].GetWorldTransform());

		/*glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
			"water"), 0);

		glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
			"cobblestone"), 1);

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"current"), cubeSides[i].GetRenderMap()->getCurrent());*/

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"currentMap"), i);

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"tileLength"), cubeSides[i].GetRenderMap()->getTileLength());

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"dimensions"), dimensions);

		glUniform1fv(glGetUniformLocation(currentShader->GetProgram(),
			"tileInfo"), dimensions * dimensions, (const GLfloat*)tileInfo);

		/*glUniform3fv(glGetUniformLocation(currentShader->GetProgram(),
			"tileInfo"), dimensions * dimensions * 2, (const GLfloat*)tileInfo);*/

		cubeSides[i].Draw(*this);

	}

	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(),
		"modelMatrix"), 1, false, (float*)&player->GetWorldTransform());

	player->Draw(*this);

	glUseProgram(0);
	SwapBuffers();

}
