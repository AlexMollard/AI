#include "Node.h"

Node::Node(Vector2 Pos, int IndexX, int IndexY)
{
	_Position = Pos;
	_IndexX = IndexX;
	_IndexY = IndexY;

	_Prev = nullptr; 
	_GScore = 0;
	_Blocked = false; 

	for (int i = 0; i < NEIGHBOUR_COUNT; i++)
	{
		_Neighbours[i] = nullptr;
		_Costs[i] = 0; 
	}
}

Node::~Node()
{

}