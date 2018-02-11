#include "Renderer.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent) {
	heightMap = new HeightMap("../Textures/terrain.raw");
	camera = new Camera();
	counter = 0;

	currentShader = new Shader("../Shaders/TexturedVertex.glsl",
		"../Shaders/TexturedFragment.glsl");

	if (!currentShader->LinkProgram()) {
		return;

	}

	heightMap->SetTexture(SOIL_load_OGL_texture(
		"../Textures/water_texture.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!heightMap->GetTexture()) {
		return;

	}
	SetTextureRepeating(heightMap->GetTexture(), true);	

	projMatrix = Matrix4::Perspective(1.0f, 1000000.0f,
		(float)width / (float)height, 45.0f);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	init = true;

}
Renderer ::~Renderer(void) {
	delete heightMap;
	delete camera;

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
		"diffuseTex"), 0);

	heightMap->t = counter;
	if (counter >= 3600) counter = 0;
	else counter++;

	//cout << counter << endl;
	//cout << heightMap->t << endl;

	heightMap->update();
	heightMap->Draw();

	glUseProgram(0);
	SwapBuffers();

}
