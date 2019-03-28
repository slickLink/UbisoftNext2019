// this file holds the defintions to the functions 
// In "TileMap.h"
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <assert.h>  
//------------------------------------------------------------------------
#include "app\app.h"


float const colorMap[6][4] =
{
	//Red, Green, Blue, Scale
	{0.0f, 0.0f, 0.0f, 1.0f}, // border / wall
	{0.38f, 0.22f, 0.38f, .015f}, //floor with coin
	{0.38f, 0.22f, 0.38f, 1.0f},// floor without coin
	{0.62f, 0.18f, 0.18f, 1.0f},// player
	{0.12f, 0.43f, 0.43f, 1.0f},// enemy
	{0.0f, 0.0f, 0.0f, 1.0f}//out of bounds
};

GTileMap::GTileMap()
{
		
	tile_width = (float)APP_VIRTUAL_WIDTH / (float)map_size;
	tile_height = (float)APP_VIRTUAL_HEIGHT / (float)map_size;
	CreateMap();
}
GTileMap::GTileMap(const int size) : map_size(size)
{
	tile_width = (float)APP_VIRTUAL_WIDTH / (float)map_size;
	tile_height = (float)APP_VIRTUAL_HEIGHT / (float)map_size;
	CreateMap();
}
GTileMap::~GTileMap()
{
}
//-------------------Funcitons-------------------------
void GTileMap::CreateMap()
{
	// create a map
	// refresh map
	for (auto &row : tileMap)
		row.assign(row.size(), mapValue::OUTOFBOUNDS);
	tileMap.resize(map_size);
	for (int i = 0; i < map_size; i++)
		tileMap[i].resize(map_size, mapValue::OUTOFBOUNDS);
	//outer columns
	float floor_covered = 0.0f;
	float target_floor_cover = 90.0f; 
	float one_tile = 100.0f / (float)((map_size - 2) * (map_size - 2));
	for (int y = 0; y < map_size; y++)
	{
		SetTileValue(0, y, mapValue::BORDER_WALL);
		SetTileValue(map_size - 1, y, mapValue::BORDER_WALL);
		floor_covered += one_tile * 2;
	}
	// outer rows
	for (int x = 1; x < map_size; x++)
	{
		SetTileValue(x, 0, mapValue::BORDER_WALL);
		SetTileValue(x, map_size - 1, mapValue::BORDER_WALL);
		floor_covered += one_tile * 2;
	}
	// inner rows and clumps
	//generate a random pacman map
	srand(time(NULL));
		
	int current_x = 1 + rand() % (map_size - 2);
	int current_y = 1 + rand() % (map_size - 2);
	int dir = rand() % 4;
		
	while (floor_covered < target_floor_cover)
	{
		int floor_length = 1 + rand() % map_size;
		int current_dir = GetNewDirection(dir, current_x, current_y);
		for (int i = 0; i < floor_length; i++)
		{
			if (!isMoveAllowed(current_x, current_y, current_dir, 0))
			{
				current_dir = GetNewDirection(current_dir, current_x, current_y);
			}
			switch (current_dir)
			{
			case 0:
				current_y += 1; break;
			case 1:
				current_x += 1; break;
			case 2:
				current_y -= 1; break;
			case 3:
				current_x -= 1; break;
			}

			if (GetTileValue(current_x, current_y) == mapValue::OUTOFBOUNDS)
			{
				floor_covered += one_tile;
				tunnel_locations.push_back(std::make_pair(current_x, current_y));
			}
			SetTileValue(current_x, current_y, mapValue::FLOOR);

		}
		dir = current_dir;
	}


}

int GTileMap::GetNewDirection(int current_dir, int x, int y)
{
	int new_dir = rand() % 2;
	if ((current_dir < 2))
		new_dir += 2;
	if (!isMoveAllowed(x, y, new_dir, 0))
	{
		switch (new_dir)
		{
		case 0:
			return 1;
		case 1:
			return 0;
		case 2:
			return 3;
		case 3:
			return 2;
		}
	}
	return new_dir;
		
}

bool GTileMap::isMoveAllowed(int x, int y, int dir, int toggle)
{
	int _x = x;
	int _y = y;
	switch (dir)
	{
	case 0:
		_y += 1; break; // north
	case 1: 
		_x += 1; break; // east
	case 2:
		_y -= 1; break; // south
	case 3:
		_x -= 1; break; // west
	}
	if(toggle == 0)
	{
		if (GetTileValue(_x, _y) == mapValue::BORDER_WALL)
			return false;
	}
	else if(toggle == 1)
	{
		if (GetTileValue(_x, _y) == mapValue::BORDER_WALL || GetTileValue(_x, _y) == mapValue::OUTOFBOUNDS)
			return false;
	}
	return true;
}

bool GTileMap::isMoveAllowed(int x, int y)
{
	int value = GetTileValue(x, y);
	if (value == mapValue::BORDER_WALL || value == mapValue::OUTOFBOUNDS)
		return false;
	return true;
}

mapValue GTileMap::GetTileValue(const int x, const int y) const
{
	// check if parameters are within bounds
	if ((x > -1 && x < map_size) && (y > -1 && y < map_size))
	{
		return tileMap[x][y];
	}
	return mapValue::OUTOFBOUNDS;
}

bool GTileMap::SetTileValue(const int x, const int y, mapValue mv)
{
	if ((x > -1 && x < map_size) && (y > -1 && y < map_size))
	{
		tileMap[x][y] = mv;
		return true;
	}
	return false;
}

void GTileMap::RenderMap() const
{
	for (int y = 0; y < map_size; y++)
	{
		for (int x = 0; x < map_size; x++)
		{
			int index = GetTileValue(x, y);
			float xPos = (x * tile_width);
			float yPos = (y * tile_height);

			App::DrawQuad(xPos, yPos, xPos + tile_width, yPos + tile_height, colorMap[index][0], colorMap[index][1], colorMap[index][2]);
		}
	}
}

std::vector<std::pair<int, int>> GTileMap::GetTunnelLocations() const
{
	return tunnel_locations;
}

std::vector<Node> GTileMap::GetNeighbours(Node node)
{
	std::vector<Node> neighbours;
	
	//check the neighbouring Nodes relative to the node passed as a parameter
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//if this is the node passed as a parameter then skip it
			if (x == 0 && y == 0)
				continue;

			int checkX = node.GetX() + x;
			int checkY = node.GetY() + y;
			int checkValue = GetTileValue(checkX, checkY);
			if (checkValue == mapValue::FLOOR || checkValue == mapValue::PLAYER)
				neighbours.push_back(Node(checkX, checkY));
		}
	}
	return neighbours;

}
