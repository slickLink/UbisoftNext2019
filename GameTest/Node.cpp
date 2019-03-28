// this file holds the defintions to the functions 
// In "Node.h"
#include "stdafx.h"

Node::Node() {}
Node::Node(int _x, int _y)
	:x(_x), y(_y){}
//---------------Functions---------------------
int Node::Get_f_cost() const
{
	return g_cost + h_cost;
}

int Node::GetX() const
{
	return x;
}

int Node::GetY() const
{
	return y;
}

int Node::GetG_cost() const
{
	return g_cost;
}

int Node::GetH_cost() const
{
	return h_cost;
}

std::pair<int, int> Node::GetParent() const
{
	return parent;
}

void Node::SetParent(int x, int y)
{
	parent = std::pair<int, int>(x, y);
}
void Node::SetX(int _x)
{
	x = _x;
}

void Node::SetY(int _y)
{
	y = _y;
}

void Node::SetG_cost(int cost)
{
	g_cost += cost;
}

void Node::SetH_cost(int cost)
{
	h_cost = cost;
}

