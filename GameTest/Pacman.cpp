// this file holds the defintions to the functions 
// In "Pacman.h"

#include "App/app.h"
#include "stdafx.h"

Pacman::Pacman()
	: x_pos(0), y_pos(0) {}

Pacman::Pacman(int x, int y)
	:x_pos(x), y_pos(y) {}

void Pacman::Move(GTileMap& map, float x_thumb, float y_thumb)
{
	int x_input = (int)round(x_thumb);
	int y_input = (int)round(y_thumb);

	switch (x_input)
	{
	case 1:
		if (map.isMoveAllowed(this->x_pos, this->y_pos, 1, 1))
		{
			this->x_pos++;
			return;
		}
	case -1:
		if (map.isMoveAllowed(this->x_pos, this->y_pos, 3, 1))
		{
			this->x_pos--;
			return;
		}
	}
	switch (y_input)
	{
	case 1:
		if (map.isMoveAllowed(this->x_pos, this->y_pos, 0, 1))
		{
			this->y_pos++;
			return;
		}
	case -1:
		if (map.isMoveAllowed(this->x_pos, this->y_pos, 2, 1))
		{
			this->y_pos--;
			return;
		}
	}
}

int Pacman::GetX() const
{
	return this->x_pos;
}

int Pacman::GetY() const
{
	return this->y_pos;
}

mapValue Pacman::GetTag() const
{
	return tag;
}


