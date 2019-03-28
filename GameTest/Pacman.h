/*
	This class is Player agent (Pacman)
*/
class Pacman
{
	//--------------------data members----------------------
	//Agent position
	int x_pos;
	int y_pos;

	//Agent tag (PLAYER)
	mapValue tag = mapValue::PLAYER;
	//-------------------constructors------------------------
public:
	Pacman();
	Pacman(int x, int y);
	//-------------------functions-------------------------------
	//This function Updates Agents position based on the map and input retrieved from a controller
	void Move(GTileMap& map, float x_thumb, float y_thumb);

	//Getters
	int GetX() const;
	int GetY() const;
	mapValue GetTag() const;
};