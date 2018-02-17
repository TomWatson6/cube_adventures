#pragma once 

class PerlinNoise {

public:
	static const int MAX_VERTICES = 256;
	static const int MAX_VERTICES_MASK = MAX_VERTICES - 1;

	PerlinNoise();

	float lerp(float a, float b, float t);
	float dotGridGradient(int ix, int iy, float x, float y);

	float noise(float x);
	float noise(float x, float y);

private:
	//Arrays of random numbers/vector2s for noise functions to work
	float r1[MAX_VERTICES];
	float r2[MAX_VERTICES][MAX_VERTICES][2];

};