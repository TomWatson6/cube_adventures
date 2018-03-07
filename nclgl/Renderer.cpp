#include "Renderer.h"
#include "../IO/CubeInput.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent) {

	CubeInput cubeInput = CubeInput();

	Map map = cubeInput.getCube(0).getMap(0);

	renderMap = new RenderMap(0, map, "../Textures/terrain.raw");
	camera = new Camera();
	counter = 0;

	currentShader = new Shader("../Shaders/TexturedVertex.glsl",
		"../Shaders/TexturedFragment.glsl");

	if (!currentShader->LinkProgram()) {
		return;

	}

	renderMap->SetTexture(SOIL_load_OGL_texture(
		"../Textures/water_texture.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!renderMap->GetTexture()) {
		return;

	}
	SetTextureRepeating(renderMap->GetTexture(), true);	
	SetTextureRepeating(renderMap->cobblestoneTexture, true);

	projMatrix = Matrix4::Perspective(1.0f, 1000000.0f,
		(float)width / (float)height, 45.0f);

	dimensions = renderMap->getDimensions();

	tileInfo = new float[dimensions * dimensions * 2];

	for (int i = 0; i < dimensions * dimensions; i++) {

		switch (renderMap->getTile(i).getType()) {
		case TileType::COBBLESTONE:
			tileInfo[i * 2] = 0;

			if (renderMap->getTile(i).getProperties().SWIMMABLE) {
				tileInfo[i * 2 + 1] = 1;
			}
			else {
				tileInfo[i * 2 + 1] = 0;
			}

			break;
		case TileType::LAVA:
			tileInfo[i * 2] = 1;

			if (renderMap->getTile(i).getProperties().SWIMMABLE) {
				tileInfo[i * 2 + 1] = 1;
			}
			else {
				tileInfo[i * 2 + 1] = 0;
			}

			break;
		case TileType::WATER:
			tileInfo[i * 2] = 2;

			if (renderMap->getTile(i).getProperties().SWIMMABLE) {
				tileInfo[i * 2 + 1] = 1;
			}
			else {
				tileInfo[i * 2 + 1] = 0;
			}

			break;
		case TileType::TERRAIN_GRASS:
			tileInfo[i * 2] = 3;

			if (renderMap->getTile(i).getProperties().SWIMMABLE) {
				tileInfo[i * 2 + 1] = 1;
			}
			else {
				tileInfo[i * 2 + 1] = 0;
			}

			break;
		case TileType::TERRAIN_SNOW:
			tileInfo[i * 2] = 4;

			if (renderMap->getTile(i).getProperties().SWIMMABLE) {
				tileInfo[i * 2 + 1] = 1;
			}
			else {
				tileInfo[i * 2 + 1] = 0;
			}

			break;
		}

	}

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
	delete renderMap;
	delete camera;
	delete[] tileInfo;

}

void Renderer::UpdateScene(float msec) {
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();
}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
		"water"), 0);

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
		"cobblestone"), 1);

	glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
		"current"), renderMap->getCurrent());

	glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
		"tileLength"), renderMap->getTileLength());

	glUniform1f(glGetUniformLocation(currentShader->GetProgram(),
		"dimensions"), dimensions);

	glUniform1fv(glGetUniformLocation(currentShader->GetProgram(),
		"tileInfo"), dimensions * dimensions * 2, (const GLfloat*)tileInfo);

	//glUniform3fv(glGetUniformLocation(currentShader->GetProgram(),
	//	"tileInfo"), dimensions * dimensions * 2, (const GLfloat*)tileInfo);

	renderMap->update();
	renderMap->Draw();

	glUseProgram(0);
	SwapBuffers();

}
