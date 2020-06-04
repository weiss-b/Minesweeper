#include "Tile.h"
#include <iostream>

Tile::Tile()
{
	mine = false;
	revealed = false;
	flag = false;
	number = false;
	recursive = false;
	locationX = 0;
	locationY = 0;
	adjacentMines = 0;
}

Tile::Tile(int x, int y)
{
	mine = false;
	revealed = false;
	flag = false;
	number = false;
	recursive = false;
	locationX = x;
	locationY = y;
	adjacentMines = 0;
}

void Tile::resetTile()
{
	mine = false;
	revealed = false;
	flag = false;
	number = false;
	recursive = false;
	adjacentMines = 0;
}


bool Tile::isMine()
{
	return mine;
}

bool Tile::isRevealed()
{
	return revealed;
}

bool Tile::setMine()
{
	if (mine == true)
		return false;
	
	mine = true;
	return true;
}

void Tile::revealNeighbor(Tile* neighbor)
{
	if (neighbor->getAdjacent() != 0)
		return;

	neighbor->setRevealed(true);
	for (int i = 0; i < neighbor->getNeighborVectorSize(); i++)
		revealNeighbor(neighbors.at(i));

	return;
}

void Tile::setRevealed(bool recursive)
{
	if (flag == true)
		return;

	revealed = true;
}

void Tile::setRevealed()
{
	if (flag == true)
		return;

	revealed = true;		
}

bool Tile::setFlag()
{
	if (revealed == false)
	{
		if (flag == true)
			flag = false;
		else
			flag = true;

		return true;
	}
	
	return false;
}

bool Tile::isFlag()
{
	return flag;
}

void Tile::setNeighbor(Tile *neighbor)
{
	if (neighbor->isMine())
	{
		adjacentMines++;
		number = true;
	}
		
	neighbors.push_back(neighbor);
}

int Tile::getAdjacent()
{
	return adjacentMines;
}

int Tile::getNeighborVectorSize()
{
	return neighbors.size();
}

std::vector<Tile*>& Tile::getVector()
{
	recursive = true;
	return neighbors;
}

bool Tile::isNumber()
{
	return number;
}

bool Tile::isRecursive()
{
	return recursive;
}
