#include "Physics.h"
#include <vector>

using namespace std;

bool Physics::validMove(Player p, Map m, Direction dir) {

	vector<Tile> tiles = m.getTiles();

	switch (dir) {
	case Direction::LEFT:
		//If not at the left side of the map
		if (p.getCurrentTile() % m.getDimensions() != 0) {
			//Make sure an index out of bounds error isn't thrown
			if (p.getCurrentTile() - 1 >= 0) {
				//If the tile to the left of it is walkable
				if (m.getTile(p.getCurrentTile() - 1).getType() == TileType::LAND) {
					return true;
				}
			}
		}
		return false;
		break;
	case Direction::RIGHT:
		//If not at the right side of the map
		if (p.getCurrentTile() % m.getDimensions() != m.getDimensions() - 1) {
			//Make sure an index out of bounds error isn't thrown
			if (p.getCurrentTile() + 1 < m.getDimensions() * m.getDimensions()) {
				//If the tile to the right of it is walkable
				if (m.getTile(p.getCurrentTile() + 1).getType() == TileType::LAND) {
					return true;
				}
			}
		}
		return false;
		break;
	case Direction::UP:
		//If not at the top of the map
		if (p.getCurrentTile() >= m.getDimensions()) {
			//If the tile above the player is walkable
			if (m.getTile(p.getCurrentTile() - m.getDimensions()).getType() == TileType::LAND) {
				return true;
			}
		}
		return false;
		break;
	case Direction::DOWN:
		//If not at the bottom of the map
		if (p.getCurrentTile() < m.getDimensions() * m.getDimensions() - m.getDimensions()) {
			//If the tile below the player is walkable
			if (m.getTile(p.getCurrentTile() + m.getDimensions()).getType() == TileType::LAND) {
				return true;
			}
		}
		return false;
	}

	return false;

}