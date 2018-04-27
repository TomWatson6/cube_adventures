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

}

Sound::~Sound() {

}

void Sound::playConfirmSound() {
	
	result = system->createSound("../Data/Sounds/confirm_sound.mp3", FMOD_3D, 0, &sound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	system->playSound(sound, NULL, false, &channel);

}

void Sound::playPlayerMoveSound() {

	result = system->createSound("../Data/Sounds/player_move_sound.mp3", FMOD_3D, 0, &sound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	system->playSound(sound, NULL, false, &channel);

}

void Sound::playInteractiveTileSound() {

	result = system->createSound("../Data/Sounds/interactive_tile_sound.mp3", FMOD_3D, 0, &sound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	system->playSound(sound, NULL, false, &channel);

}

void Sound::playSwapSound() {

	result = system->createSound("../Data/Sounds/swap_sound.mp3", FMOD_3D, 0, &sound);

	if (result != FMOD_OK) {
		cout << "Problem with creating sound!" << endl;
		exit(-1);
	}

	system->playSound(sound, NULL, false, &channel);

}