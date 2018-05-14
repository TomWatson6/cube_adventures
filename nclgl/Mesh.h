# pragma once
#include "OGLRenderer.h"

//#include <string>

using std::string;

enum MeshBuffer {
	VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, INDEX_BUFFER, MAX_BUFFER
	
};
class Mesh {
public:
	Mesh(void);
	~Mesh(void);
	virtual void Draw();
	static Mesh * GenerateTriangle();
	static Mesh* LoadMeshFile(const string &filename);
	void SetTexture(GLuint tex) { texture = tex; }
	GLuint GetTexture() { return texture; }
	static Mesh * GenerateQuad();
	void setColour(Vector4 colour);
	void updateAlpha(float alpha);
	void setAlpha(float alpha);
	float getAlpha();

	GLuint cobblestoneTexture;

		
protected:
	void BufferData();
	void RebufferData();
	GLuint numIndices;
	unsigned int * indices;

	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint type;
	Vector3 * vertices;
	Vector4 * colours;
	GLuint texture;
	Vector2 * textureCoords;
	
};
