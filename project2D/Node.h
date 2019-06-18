#pragma once
#include "Vector2.h"

#define NEIGHBOUR_COUNT 4

struct Node
{
	Node(Vector2 Pos, int IndexX, int IndexY);
	~Node();

	Vector2 _Position;
	int _IndexX;
	int _IndexY;

	Node* _Prev;
	int _GScore;
	Node* _Neighbours[NEIGHBOUR_COUNT]; 
	int _Costs[NEIGHBOUR_COUNT]; 
 	bool _Blocked; 
};