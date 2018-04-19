#include "Player.h"

void Player::move(Direction dir) {

	isMoving = true;
	dirMoving = dir;

	//Use Cyclogon class to calculate relevant position and rotation

}

void Player::update() {

	if (isMoving && progress != 90) {

		switch (dirMoving) {
		case Direction::LEFT:
			//negative x

		case Direction::RIGHT:
			//positive x
		case Direction::UP:
			//positive y
		case Direction::DOWN:
			//negative y
		}

	}

}