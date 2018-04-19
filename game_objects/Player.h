#pragma once

enum class Direction { LEFT, RIGHT, UP, DOWN };

class Player {

private:
	float posx;
	float posy;
	float posz;

	float rotx = 0;
	float roty = 0;
	float rotz = 0;

	float sideLength;

	bool isMoving;
	Direction dirMoving;

	//Shows the current degrees of progress of the 90 degree rotation whilst the player is moving
	int progress = 0;

public:
	Player(float posx, float posy, float posz, float sideLength) {
		this->posx = posx;
		this->posy = posy;
		this->posz = posz;
		this->sideLength = sideLength;
	}

	void setPos(float x, float y, float z) {
		this->posx = x;
		this->posy = y;
		this->posz = z;
	}

	void setRot(float x, float y, float z) {
		this->rotx = x;
		this->roty = y;
		this->rotz = z;
	}

	float getPosx() { return posx; }
	float getPosy() { return posy; }
	float getPosz() { return posz; }

	float getRotx() { return rotx; }
	float getRoty() { return roty; }
	float getRotz() { return rotz; }

	//Will check to see if the cube can move in that direction -- ADD TO PHYSICS
	bool isValidMove(Player p, Direction dir);

	//Appear somewhere, given a tile
	//Fade out

	void move(Direction dir);

	void update();

};