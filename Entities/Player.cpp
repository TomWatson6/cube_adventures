#include "Player.h"

void Player::move(Direction dir) {

	isMoving = true;
	dirMoving = dir;

	switch (dir) {
	case Direction::LEFT:
		pivotx = posx - 0.5 * sideLength;
		break;
	case Direction::RIGHT:
		pivotx = posx + 0.5 * sideLength;
		break;
	case Direction::UP:
		pivoty = posy + 0.5 * sideLength;
		break;
	case Direction::DOWN:
		pivoty = posy - 0.5 * sideLength;

	}

}

void Player::update() {

	if (isMoving && progress < 90) {

		progress += ROTARY_STEP;

		float angle = progress + 45;
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
	else {
		isMoving = false;
		progress = 0;
	}

}