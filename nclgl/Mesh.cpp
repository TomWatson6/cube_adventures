#include "Mesh.h"

Mesh::Mesh(void) {
	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
		
	}
	glGenVertexArrays(1, &arrayObject);
	indices = NULL;
	numIndices = 0;
	texture = 0;
	textureCoords = NULL;
	numVertices = 0;
	vertices = NULL;
	colours = NULL;
	type = GL_TRIANGLES;

	cobblestoneTexture = SOIL_load_OGL_texture(
		"../Textures/cobblestone.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	
}

Mesh ::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);
	glDeleteBuffers(MAX_BUFFER, bufferObject);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &cobblestoneTexture);
	delete[] indices;
	delete[] textureCoords;
	delete[] vertices;
	delete[] colours;
	
}

Mesh * Mesh::GenerateTriangle() {
	Mesh * m = new Mesh();
	m -> numVertices = 3;
	
	m -> vertices = new Vector3[m -> numVertices];
	m -> vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	m -> vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	m -> vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);
	
	m -> textureCoords = new Vector2[m -> numVertices];
	m -> textureCoords[0] = Vector2(0.5f, 0.0f);
	m -> textureCoords[1] = Vector2(1.0f, 1.0f);
	m -> textureCoords[2] = Vector2(0.0f, 1.0f);

	m -> colours = new Vector4[m -> numVertices];
	
	m -> colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m -> colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m -> colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	
	m -> BufferData();
	return m;
}

Mesh* Mesh::LoadMeshFile(const string &filename) {
	ifstream f(filename);

	if (!f) {
		return NULL;
	}

	Mesh*m = new Mesh();
	f >> m->numVertices;

	int hasTex = 0;
	int hasColour = 0;

	f >> hasTex;
	f >> hasColour;

	m->vertices = new Vector3[m->numVertices];

	if (hasTex) {
		m->textureCoords = new Vector2[m->numVertices];
		m->colours = new Vector4[m->numVertices];
	}

	for (unsigned int i = 0; i < m->numVertices; ++i) {
		f >> m->vertices[i].x;
		f >> m->vertices[i].y;
		f >> m->vertices[i].z;
	}

	if (hasColour) {
		for (unsigned int i = 0; i < m->numVertices; ++i) {
			unsigned char r, g, b, a;

			f >> r;
			f >> g;
			f >> b;
			f >> a;
			//OpenGL can use floats for colours directly - this will take up 4x as
			//much space, but could avoid any byte / float conversions happening
			//behind the scenes in our shader executions
			m->colours[i] = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}
	}

	if (hasTex) {
		for (unsigned int i = 0; i < m->numVertices; ++i) {
			f >> m->textureCoords[i].x;
			f >> m->textureCoords[i].y;
		}
	}

	m->BufferData();
	return m;
}

void Mesh::BufferData() {
	glBindVertexArray(arrayObject);
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3),
		vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);
	if (textureCoords) { // This bit is new !
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector2),
			textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
		
	}
	if (indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint),
			indices, GL_STATIC_DRAW);
		
	}

	if (colours) {
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4),
			colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	
	}
	glBindVertexArray(0);
	
}

void Mesh::RebufferData() {

	//int offset = numVertices * sizeof(Vector3);

	//glBindVertexArray(arrayObject);
	//glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(Vector3),
		vertices);
	//glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(VERTEX_BUFFER);
	if (textureCoords) { // This bit is new !
		//glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(Vector2),
			textureCoords);
		//glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(TEXTURE_BUFFER);

		//offset += numVertices * sizeof(Vector2);

	}
	if (indices) {

		//glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			bufferObject[INDEX_BUFFER]);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, numIndices * sizeof(GLuint),
			indices);

		//offset += numIndices * sizeof(GLuint);

	}

	if (colours) {
		//glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(Vector4),
			colours);
		//glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(COLOUR_BUFFER);

	}
	//glBindVertexArray(0);

}

void Mesh::Draw() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, cobblestoneTexture);

	glBindVertexArray(arrayObject);
	if (bufferObject[INDEX_BUFFER]) {
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
		
	}
	else {
		glDrawArrays(type, 0, numVertices);
		
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);	
}

Mesh * Mesh::GenerateQuad() {
	Mesh * m = new Mesh();
	m -> numVertices = 4;
	m -> type = GL_TRIANGLE_STRIP;
	
	m -> vertices = new Vector3[m -> numVertices];
	m -> textureCoords = new Vector2[m -> numVertices];
	m -> colours = new Vector4[m -> numVertices];
	
	m -> vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	m -> vertices[1] = Vector3(-1.0f, 1.0f, 0.0f);
	m -> vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
	m -> vertices[3] = Vector3(1.0f, 1.0f, 0.0f);
	
	m -> textureCoords[0] = Vector2(0.0f, 1.0f);
	m -> textureCoords[1] = Vector2(0.0f, 0.0f);
	m -> textureCoords[2] = Vector2(1.0f, 1.0f);
	m -> textureCoords[3] = Vector2(1.0f, 0.0f);
	
	for (int i = 0; i < 4; ++i) {
		m -> colours[i] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		
	}
	
	m -> BufferData();
	return m;
	
}
