// this file holds the defintions to the functions 
// In "Ghost.h"
#include "stdafx.h"


Ghost::Ghost()
	: x_pos(0), y_pos(0) {}

Ghost::Ghost(int x, int y)
	: x_pos(x), y_pos(y) {}

void Ghost::Move(GTileMap& map, Pacman target)
{
	std::pair<int, int> currentMove = this->tracking_list[this->tracking_list.size() - 1];
	if (map.isMoveAllowed(currentMove.first, currentMove.second))
	{
		this->x_pos = currentMove.first;
		this->y_pos = currentMove.second;
	}
	this->tracking_list.pop_back();
}

int Ghost::GetX() const
{
	return this->x_pos;
}

int Ghost::GetY() const
{
	return this->y_pos;
}

mapValue Ghost::GetTag() const
{
	return tag;
}

std::vector<std::pair<int, int>> Ghost::GetMoves() const
{
	return this->tracking_list;
}

void Ghost::SetList(std::vector<std::pair<int, int>> l)
{
	this->tracking_list = l;
}

