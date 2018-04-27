#include "Player.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

void Player::move(Direction dir, int dimensions) {

	isMoving = true;
	dirMoving = dir;

	switch (dir) {
	case Direction::LEFT:
		pivotx = posx - 0.5 * sideLength;
		currentTile -= 1;
		cout << "LEFT" << endl;
		break;
	case Direction::RIGHT:
		pivotx = posx + 0.5 * sideLength;
		currentTile += 1;
		cout << "RIGHT" << endl;
		break;
	case Direction::UP:
		pivoty = posy + 0.5 * sideLength;
		currentTile -= dimensions;
		cout << "UP" << endl;
		break;
	case Direction::DOWN:
		pivoty = posy - 0.5 * sideLength;
		currentTile += dimensions;
		cout << "DOWN" << endl;

	}

	cout << currentTile << endl;

}

void Player::update(Sound sound) {

	if (isMoving && progress < 90) {

		progress += ROTARY_STEP;

		float angle = (progress + 45) * M_PI / 180.0;
		posz = pivotz + radius * sin(angle);

		switch (dirMoving) {
		case Direction::LEFT:
			//negative x

			posx = pivotx + radius * cos(angle);			

			break;

		case Direction::RIGHT:
			//positive x

			posx = pivotx - radius * cos(angle);

			break;

		case Direction::UP:
			//positive y

			posy = pivoty - radius * cos(angle);

			break;

		case Direction::DOWN:
			//negative y

			posy = pivoty + radius * cos(angle);

		}

	}
	else if (progress >= 90 && isMoving) {
		triggerPulse = true; //Create this bool in player -- to tell main loop to pulse
		progress = 0;
		isMoving = false;
		tileFrom = currentTile;
		sound.playPlayerMoveSound();
	}
	else {
		triggerPulse = false;
	}

}