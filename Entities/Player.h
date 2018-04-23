#pragma once
#include <math.h>

enum class Direction { LEFT, RIGHT, UP, DOWN };

static const float ROTARY_STEP = 4.0f;

class Player {

private:
	float posx;
	float posy;
	float posz;

	int currentTile;

	float sideLength;

	//This will be used to calculate the movement of the player
	float radius;
	float pivotx;
	float pivoty;
	float pivotz;

	bool isMoving = false;
	Direction dirMoving = Direction::RIGHT;

	//Shows the current degrees of progress of the 90 degree rotation whilst the player is moving
	float progress = 0;

public:

	Player(float posx, float posy, float posz, float sideLength, int currentTile) {
		this->posx = posx;
		this->posy = posy;
		this->posz = posz;
		this->pivotz = posz;
		this->sideLength = sideLength;
		this->currentTile = currentTile;
		this->radius = sqrt(0.5 * sideLength * sideLength);
	}

	void setPos(float x, float y, float z) {
		this->posx = x;
		this->posy = y;
		this->posz = z;
	}

	void setCurrentTile(int currentTile) {
		this->currentTile = currentTile;
	}

	float getPosx() { return posx; }
	float getPosy() { return posy; }
	float getPosz() { return posz; }

	bool getIsMoving() { return isMoving; }
	int getCurrentTile() { return currentTile; }
	Direction getDirection() { return dirMoving; }
	int getProgress() { return progress; }

	//Appear somewhere, given a tile
	//Fade out

	void move(Direction dir, int dimensions);

	void update();

};