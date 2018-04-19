#pragma once
#include "../Entities/Player.h"
#include "../game_objects/Map.h"

class Physics {

public:
	bool validMove(Player p, Map m, Direction dir);

};