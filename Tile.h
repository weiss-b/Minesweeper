#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Tile
{
	bool mine, revealed, flag, number, recursive;
	int locationX, locationY, adjacentMines;
	std::vector<Tile*> neighbors;
	void revealNeighbor(Tile* neighbor);

public:
	Tile();
	Tile(int x, int y);
	bool isMine();
	bool isRevealed();
	bool setMine();
	bool isFlag();
	bool isNumber();
	bool isRecursive();
	bool setFlag();
	void setRevealed();
	void setRevealed(bool recursive);
	void setNeighbor(Tile* neighbor);
	void resetTile();
	int getAdjacent();
	int getNeighborVectorSize();
	std::vector<Tile*>& getVector();
};

