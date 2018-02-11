#pragma once 

class PerlinNoise {

private:
	float r[256][256][2];

public:
	PerlinNoise();

	void initialiseGradient();
	float lerp(float a, float b, float t);
	float dotGridGradient(int ix, int iy, float x, float y);
	float noise(float x, float y);

};