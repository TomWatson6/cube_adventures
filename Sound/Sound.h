#pragma once

#include <string>
#include "fmod.hpp"
#include "fmod_errors.h"

using namespace std;

class Sound {

public:
	Sound();
	~Sound();

	void playPlayerMoveSound();
	void playConfirmSound();
	void playInteractiveTileSound();
	void playSwapSound();

	FMOD_RESULT result;
	FMOD::System *system;
	FMOD::Sound *sound;
	FMOD::Channel *channel = NULL;

};