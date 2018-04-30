#include "Sound.h"
#include <iostream>

using namespace std;

Sound::Sound() {

	result = FMOD::System_Create(&system);

	if (result != FMOD_OK) {
		cout << "Sound Error" << endl;
		exit(-1);
	}

	result = system->init(512, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK) {
		cout << "Sound Error" << endl;
		exit(-1);
	}

	result = system->createSound("../Data/Sounds/confirm_sound.mp3", FMOD_3D, 0, &confirmSound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	result = system->createSound("../Data/Sounds/player_move_sound.mp3", FMOD_3D, 0, &playerMoveSound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	result = system->createSound("../Data/Sounds/interactive_tile_sound.mp3", FMOD_3D, 0, &interactiveTileSound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	result = system->createSound("../Data/Sounds/swap_sound.mp3", FMOD_3D, 0, &swapSound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

}

Sound::~Sound() {

	//delete sound;
	//delete channel;
	//system->close();
	//delete &system;

}

void Sound::playConfirmSound() {

	system->update();

	system->playSound(confirmSound, NULL, false, &channel);

}

void Sound::playPlayerMoveSound() {

	system->update();

	system->playSound(playerMoveSound, NULL, false, &channel);

}

void Sound::playInteractiveTileSound() {

	system->update();

	system->playSound(interactiveTileSound, NULL, false, &channel);
	
}

void Sound::playSwapSound() {

	system->update();

	system->playSound(swapSound, NULL, false, &channel);

}