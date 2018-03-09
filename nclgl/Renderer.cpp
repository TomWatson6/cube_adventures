#include "Renderer.h"
#include "../IO/CubeInput.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent) {

	CubeInput cubeInput = CubeInput();

	cubeSides = new MapNode*[Cube::CUBE_SIDES];

	GLuint texture = SOIL_load_OGL_texture(
		"../Textures/water_texture.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		Map map = cubeInput.getCube(0).getMap(i);

		RenderMap* renderMap = new RenderMap(i, map, "../Textures/terrain.raw");

		renderMap->SetTexture(texture);

		if (!renderMap->GetTexture()) {
			return;
		}

		SetTextureRepeating(renderMap->GetTexture(), true);
		SetTextureRepeating(renderMap->cobblestoneTexture, true);

		dimensions = renderMap->getDimensions();

		tileInfo = new float[dimensions * dimensions * 2];

		for (int j = 0; j < dimensions * dimensions; j++) {

			switch (renderMap->getTile(j).getType()) {
			case TileType::COBBLESTONE:
				tileInfo[j * 2] = 0;

				if (renderMap->getTile(j).getProperties().SWIMMABLE) {
					tileInfo[j * 2 + 1] = 1;
				}
				else {
					tileInfo[j * 2 + 1] = 0;
				}

				break;
			case TileType::LAVA:
				tileInfo[j * 2] = 1;

				if (renderMap->getTile(j).getProperties().SWIMMABLE) {
					tileInfo[j * 2 + 1] = 1;
				}
				else {
					tileInfo[j * 2 + 1] = 0;
				}

				break;
			case TileType::WATER:
				tileInfo[j * 2] = 2;

				if (renderMap->getTile(j).getProperties().SWIMMABLE) {
					tileInfo[j * 2 + 1] = 1;
				}
				else {
					tileInfo[j * 2 + 1] = 0;
				}

				break;
			case TileType::TERRAIN_GRASS:
				tileInfo[j * 2] = 3;

				if (renderMap->getTile(j).getProperties().SWIMMABLE) {
					tileInfo[j * 2 + 1] = 1;
				}
				else {
					tileInfo[j * 2 + 1] = 0;
				}

				break;
			case TileType::TERRAIN_SNOW:
				tileInfo[j * 2] = 4;

				if (renderMap->getTile(j).getProperties().SWIMMABLE) {
					tileInfo[j * 2 + 1] = 1;
				}
				else {
					tileInfo[j * 2 + 1] = 0;
				}

				break;
			}

		}

		Vector4 colour = Vector4(1, 1, 1, 1);

		cubeSides[i] = new MapNode(renderMap, colour);

		//cubeSides[i]->SetModelScale(Vector3(i / 6, i / 6, i / 6));

	}

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {
		cubeSides[i]->SetTransform(Matrix4::Translation(Vector3(0, 0, 15 * RAW_WIDTH * HEIGHTMAP_Z)));
	}

	Matrix4 transform1 = Matrix4::Rotation(90.0f, Vector3(1, 0, 0));
	Matrix4 transform2 = Matrix4::Translation(Vector3(0, 0, 1));
	Matrix4 transform3 = Matrix4::Translation(Vector3(1, 0, 0));
	Matrix4 transform4 = Matrix4::Rotation(90.0f, Vector3(0, 0, 1));

	Matrix4 modelMatrix;

	for (int i = 0; i < Cube::CUBE_SIDES / 2; i++) {

		modelMatrix = transform1 * transform2;

		cubeSides[i * 2]->SetTransform(cubeSides[i * 2]->GetWorldTransform() * modelMatrix);

		modelMatrix = modelMatrix * transform3 * transform4;

		cubeSides[i * 2 + 1]->SetTransform(cubeSides[i * 2 + 1]->GetWorldTransform() * modelMatrix);

	}

	/*Map map = cubeInput.getCube(0).getMap(0);

	renderMap = new RenderMap(0, map, "../Textures/terrain.raw");*/
	camera = new Camera();
	counter = 0;

	currentShader = new Shader("../Shaders/TexturedVertex.glsl",
		"../Shaders/TexturedFragment.glsl");

	if (!currentShader->LinkProgram()) {
		return;

	}

	projMatrix = Matrix4::Perspective(1.0f, 1000000.0f,
		(float)width / (float)height, 45.0f);



	for (int i = 0; i < dimensions * dimensions * 2; i++) {
		cout << tileInfo[i];
	}
	cout << endl;

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	init = true;

}
Renderer ::~Renderer(void) {
	delete cubeSides;
	delete camera;
	delete[] tileInfo;

}

void Renderer::UpdateScene(float msec) {
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {
		cubeSides[i]->Update(msec);
	}

}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();

	for (int i = 0; i < Cube::CUBE_SIDES; i++) {

		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), 
			"modelMatrix"), 1, true, (float*)&cubeSides[i]->GetTransform());

		glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
			"water"), 0);

		glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
			"cobblestone"), 1);

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"current"), cubeSides[i]->GetRenderMap()->getCurrent());

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"tileLength"), cubeSides[i]->GetRenderMap()->getTileLength());

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
			"dimensions"), dimensions);

		glUniform1fv(glGetUniformLocation(currentShader->GetProgram(),
			"tileInfo"), dimensions * dimensions * 2, (const GLfloat*)tileInfo);

		//glUniform3fv(glGetUniformLocation(currentShader->GetProgram(),
		//	"tileInfo"), dimensions * dimensions * 2, (const GLfloat*)tileInfo);

		cubeSides[i]->Draw(*this);

	}

	glUseProgram(0);
	SwapBuffers();

}
