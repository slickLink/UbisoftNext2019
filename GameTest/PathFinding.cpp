// this file holds the defintions to the functions 
// In "PathFinding.h"
#include "stdafx.h"

bool operator==(const Node& a, const Node& b)
{
	return (a.GetX() == b.GetX() && a.GetY() == b.GetY());
}
bool operator< (const Node& a, const Node& b)
{
	return (b.Get_f_cost() < a.Get_f_cost());
}

std::vector<std::pair<int, int>> FindPath(int start_x, int start_y, int target_x, int target_y, GTileMap g)
{
	Node startNode = Node(start_x, start_y);
	Node targetNode = Node(target_x, target_y);

	//create OPEN and CLOSED(explored) set of Nodes
	std::priority_queue<Node> open;
	std::vector<Node> explored;
	
	//add the start node to the open set
	open.push(startNode);

	while (open.size() > 0)
	{
		Node currentNode = open.top();
		open.pop();
		explored.push_back(currentNode);

		// if goal test
		if (currentNode == targetNode)
		{
			std::vector<std::pair<int, int>> backtrack = retrace(currentNode, explored, startNode);
			return backtrack;
		}
		// get currentNodes Neighbours
		std::vector<Node> neigbours = g.GetNeighbours(currentNode);
		for (Node neighbour : neigbours)
		{
			if (contains(explored, neighbour))
				continue;

			int cost = currentNode.GetG_cost() + FindManhattanDistance(currentNode, neighbour);
			if ((!contains(open, neighbour) || cost < neighbour.GetG_cost()))
			{
				neighbour.SetG_cost(cost);
				neighbour.SetH_cost(FindManhattanDistance(neighbour, targetNode));
				neighbour.SetParent(currentNode.GetX(), currentNode.GetY());
				open.push(neighbour);
			}
		}
	}
	return std::vector<std::pair<int, int>>();
}

int FindManhattanDistance(Node a, Node b)
{
	int distance = abs(a.GetX() - b.GetX()) + abs(a.GetY() - b.GetY());
	return distance;
}


bool contains(std::vector<Node> check, Node a)
{
	for (auto node : check)
	{
		if (node == a)
			return true;
	}
	return false;
}
bool contains(std::priority_queue<Node> check, Node a)
{
	while (check.size() > 0)
	{
		Node temp = check.top();
		if (a == temp)
			return true;
		check.pop();
	}
	return false;
}
std::vector<std::pair<int, int>> retrace(Node parent, std::vector<Node> trace, Node target)
{
	std::vector<std::pair<int, int>> traced;
	Node currentNode = parent;
	while (!(currentNode == target))
	{
		for (auto node : trace)
		{
			if (currentNode.GetParent().first == node.GetX() && currentNode.GetParent().second == node.GetY())
			{
				traced.push_back(currentNode.GetParent());
				currentNode = node;
				break;
			}
		}
	}
	return traced;
	
}

