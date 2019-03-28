/*
	This class is AI agent (Ghost)
*/
class Ghost
{
	//--------------------data members----------------------
	//Agent position
	int x_pos;
	int y_pos;

	//List of positions to some agent(Pacman)
	std::vector<std::pair<int, int>> tracking_list;

	//Agent tag (Ghost)
	mapValue tag = mapValue::GHOST;
	//-------------------constructors------------------------
public:
	Ghost();
	Ghost(int x, int y);
	//-------------------functions-------------------------------
	//This function Updates Agents position based on the map as it moves towards the target (a Pacman instance)
	void Move(GTileMap& map, Pacman target);

	//This is a setter for the agent's tracking_list
	void SetList(std::vector<std::pair<int, int>> l);

	//These are self explanitory getters of the Agent
	int GetX() const;
	int GetY() const;
	mapValue GetTag() const;
	std::vector<std::pair<int, int>> GetMoves() const;
};