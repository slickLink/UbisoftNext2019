#include "stdafx.h"

enum mapValue
{
	OUTOFBOUNDS = 5,
	BORDER_WALL = 0,
	FLOOR_WITH_COIN = 1, // for future expansion that enables the player to collects coins while trying to survive
	FLOOR= 2,
	PLAYER = 3,
	GHOST = 4
};

/*
	This class is the Tile Map

	Note: Direction in this simulation is as follows
	0: up/North
	1: Right/East
	2: down/South
	3: Left/West
*/
class GTileMap
{
	//-----------------data members-----------------------
	//Tile map size
	int map_size = 20;

	//individual tile dimensions
	float tile_width;
	float tile_height;

	//Actual map
	std::vector<std::vector<mapValue>> tileMap;

	//A list of walkable locations on the map
	std::vector<std::pair<int, int>> tunnel_locations;
	//------------------contructors-----------------------
public:
	GTileMap();
	GTileMap(const int size);
	~GTileMap();
	//-------------------Funcitons-------------------------
	// This function generates a random Tile Map
	void CreateMap();

	// This functions retrieves the tile value at given coordinates
	mapValue GetTileValue(const int x, const int y) const;

	// This functions assigns a tile value at the given coordinates with the given mapValue
	bool SetTileValue(const int x, const int y, mapValue mv);

	//This Functions renders the Tile map to the application window
	void RenderMap() const;

	// This function has two uses (Toggle indicates the uses)
	// When toggle = 0. returns true when a move given direction and previous coordinates (used for random map generation)
	// When toggle = 1. returns true when a move given direction and previous coordinates is Traversable (For any function excluding GTileMap::CreateMap)
	bool isMoveAllowed(int x, int y, int dir, int toggle);

	//This functions checks if the given coordinates are traversable
	bool isMoveAllowed(int x, int y);

	//This function is used GTileMap::CreateMap
	int GetNewDirection(int current_dir, int x, int y);

	//This functions returns a vector of Traversable coordinates
	std::vector<std::pair<int, int>> GetTunnelLocations() const;

	//This Functions returns a vector of Traversable Neighbouring Nodes given a Node
	//This funtions is used for PathFinding.
	std::vector<Node> GetNeighbours(Node node);
};
