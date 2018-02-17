#include "PerlinNoise.h"
#include <cstdlib>

PerlinNoise::PerlinNoise() {

	//Initialise array for 1D Perlin Noise
	for (int i = 0; i < MAX_VERTICES; i++) {
		r1[i] = rand();
	}

	//Initialise array for 2D Perlin Noise
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			r2[i][j][0] = rand();
			r2[i][j][1] = rand();

			float magnitude = pow((pow(r2[i][j][0], 2) + pow(r2[i][j][1], 2)), 0.5);
			r2[i][j][0] = r2[i][j][0] / magnitude;
			r2[i][j][1] = r2[i][j][1] / magnitude;
		}
	}

}

//void PerlinNoise::initialiseGradient() {
//
//	for (int i = 0; i < numVertices; i++) {
//		Vector2 v = Vector2(rand(), rand());
//
//		float magnitude = pow((pow(v.x, 2) + pow(v.y, 2)), 0.5);
//		v.x = v.x / magnitude;
//		v.y = v.y / magnitude;
//
//		Gradient[i] = v;
//	}
//
//}

//Function to lineraly interpolate between a0 and a1
//Weight w should be in the range [0.0, 1.0]
float PerlinNoise::lerp(float a, float b, float t) {
	return (1.0 - t) * a + t * b;
}

//Computers the dot product of the distance and gradient vectors
float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y) {

	//Precomputed (or otherwise) gradient vectors at each grid node

	//Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	//Compute the dot-product
	return (dx * r2[ix % MAX_VERTICES_MASK][iy % MAX_VERTICES_MASK][0] + 
		dy * r2[ix % MAX_VERTICES_MASK][iy % MAX_VERTICES_MASK][1]);
}

//Compute Perlin noise at coordinate x (1D Version)
float PerlinNoise::noise(float x) {

	int x0 = (int)x;
	int x1 = x0 + 1;
	float sx = x - x0;
	float sxRemapSmoothStep = sx * sx * (3 - 2 * sx);

	int xMin = x0 % MAX_VERTICES_MASK;
	int xMax = (xMin + 1) % MAX_VERTICES_MASK;

	float ix = lerp(r1[xMin], r1[xMax], sxRemapSmoothStep);

	return ix;

}

//Compute Perlin noise at coordinates x, y (2D Version)
float PerlinNoise::noise(float x, float y) {

	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	float sx = x - x0;
	float sy = y - y0;
	float sxRemapSmoothStep = sx * sx * (3 - 2 * sx);
	float syRemapSmoothStep = sy * sy * (3 - 2 * sy);

	/*int xMin = x0 % MAX_VERTICES_MASK;
	int xMax = (xMin + 1) % MAX_VERTICES_MASK;*/

	float n0, n1, ix0, ix1, value;

	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = lerp(n0, n1, sxRemapSmoothStep);
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = lerp(n0, n1, sxRemapSmoothStep);

	value = lerp(ix0, ix1, syRemapSmoothStep);

	return value;

	//float y = lerp(r[xMin], r[xMax], sxRemapSmoothStep);

	//return y;

	////Determine grid cell coordinates
	//int x0 = (int)x;
	//int x1 = x0 + 1;
	//int y0 = (int)y;
	//int y1 = y0 + 1;

	////Determine interpolation weights
	////Could also use higher order polynomial/s-curve here
	//float sx = x - (float)x0;
	//float sy = y - (float)y0;

	////Interpolate between grid point gradients
	//float n0, n1, ix0, ix1, value;

	//n0 = dotGridGradient(x0, y0, x, y);
	//n1 = dotGridGradient(x1, y0, x, y);
	//ix0 = lerp(n0, n1, sx);
	//n0 = dotGridGradient(x0, y1, x, y);
	//n1 = dotGridGradient(x1, y1, x, y);
	//ix1 = lerp(n0, n1, sx);

	//value = lerp(ix0, ix1, sy);

	//return value;

}