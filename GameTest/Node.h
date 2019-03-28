/*
	This class describes a Node 
	This class is used for A* Pathfinding algorithm
*/
class Node
{
	//---------------data Members-----------------
	// coordinates
	int x;
	int y;

	// Node specific g and h costs
	int g_cost = 0;
	int h_cost = 0;
	
	// Coordinated to the parent of the Node
	std::pair<int, int> parent;
public:
	//---------------Constructors-----------------
	Node();
	Node(int _x, int _y);
	//---------------Functions---------------------
	// returns the Nodes heuristic fuction f(n) = g_cost + h_cost
	int Get_f_cost() const;

	// Self explanitory Getters
	int GetX() const;
	int GetY() const;
	int GetG_cost() const;
	int GetH_cost() const;
	std::pair<int, int> GetParent() const;

	// Self explanitory Setters
	void SetParent(int x, int y);
	void SetX(int _x);
	void SetY(int _y);
	void SetG_cost(int cost);
	void SetH_cost(int cost);
};
