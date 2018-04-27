#pragma once
#include <math.h>
#include "../Sound/Sound.h"

enum class Direction { LEFT, RIGHT, UP, DOWN };

static const float ROTARY_STEP = 4.0f;

class Player {

private:
	float posx;
	float posy;
	float posz;

	bool triggerPulse = false;

	int currentTile;

	float sideLength;

	//This will be used to calculate the movement of the player
	float radius;
	float pivotx;
	float pivoty;
	float pivotz;

	//Sound sound = Sound();

	int tileFrom;

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
		this->tileFrom = currentTile;
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

	bool getTriggerPulse() { return triggerPulse; }
	bool getIsMoving() { return isMoving; }
	int getCurrentTile() { return currentTile; }
	Direction getDirection() { return dirMoving; }
	int getProgress() { return progress; }
	int getTileFrom() { return tileFrom; }

	void setTriggerPulse(bool triggerPulse) { this->triggerPulse = triggerPulse; }

	//Appear somewhere, given a tile
	//Fade out

	void move(Direction dir, int dimensions);

	void update(Sound sound);

};