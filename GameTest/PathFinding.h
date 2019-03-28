/*These are funtions used for A* Pathfinding*/
//---------------Functions---------------------
// returns a vector of coordinates(The path found) from the given start and target coordinates as well as the Map geography
std::vector<std::pair<int, int>> FindPath(int start_x, int start_y, int target_x, int target_y, GTileMap g);

// returns the Manhattan distance between the given Nodes
int FindManhattanDistance(Node a, Node b);

// These two Functions check if a node in a data structure
bool contains(std::vector<Node> check, Node a);
bool contains(std::priority_queue<Node> check, Node a);

// This function returns the vector of coordinates(used When FindPath() finds a path)
std::vector<std::pair<int, int>> retrace(Node parent, std::vector<Node> trace, Node target);

