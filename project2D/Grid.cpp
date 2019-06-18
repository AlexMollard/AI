#include "Grid.h"
#include "Node.h"
#include "Vector2.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <random>

#define SQUARE_SIZE 40
#define GRID_POSX 10
#define GRID_POSY 10

Grid::Grid(int Width, int Height, int screenWidth, int screenHeight)
{
	_Width = Width; 
	_Height = Height; 

	_NodeList = new Node**[_Width];

	for (int i = 0; i < _Width; i++)
	{
		_NodeList[i] = new Node * [_Height]; 
	}

	for (int x = 0; x < _Width; x++)
	{
		for (int  y = 0; y < _Height; y++)
		{
			Vector2 pos;
			pos.x = x * SQUARE_SIZE + GRID_POSX;
			pos.y = y * SQUARE_SIZE + GRID_POSY;
			_NodeList[x][y] = new Node(pos, x, y); 
		}
	}

	for (int x = 0; x < _Width; ++x)
	{
		for (int y = 0; y < _Height; ++y)
		{
			if (y > 0)
				_NodeList[x][y]->_Neighbours[0] = _NodeList[x][y - 1];	//Down

			if (x > 0)
				_NodeList[x][y]->_Neighbours[1] = _NodeList[x - 1][y];	//Left

			if (y < _Height - 1)
				_NodeList[x][y]->_Neighbours[2] = _NodeList[x][y + 1];	//Up

			if (x < _Width - 1)
				_NodeList[x][y]->_Neighbours[3] = _NodeList[x + 1][y];	//Right

			if (x < _Width - 1 && y < _Height - 1)
				_NodeList[x][y]->_Neighbours[4] = _NodeList[x + 1][y + 1];	//Right Up

			if (x < _Width - 1 && y > 0)
				_NodeList[x][y]->_Neighbours[5] = _NodeList[x + 1][y - 1];	//Right down

			if (x > 0 && y > 0)
				_NodeList[x][y]->_Neighbours[6] = _NodeList[x - 1][y - 1];	//Left down

			if (x > 0 && y < _Height - 1)
				_NodeList[x][y]->_Neighbours[7] = _NodeList[x - 1][y + 1];	//Left Up

			// Adjacent
			_NodeList[x][y]->_Costs[0] = 10;
			_NodeList[x][y]->_Costs[1] = 10;
			_NodeList[x][y]->_Costs[2] = 10;
			_NodeList[x][y]->_Costs[3] = 10;	

			// Diagonal
			_NodeList[x][y]->_Costs[4] = 14;
			_NodeList[x][y]->_Costs[5] = 14;
			_NodeList[x][y]->_Costs[6] = 14;
			_NodeList[x][y]->_Costs[7] = 14;
		}
	}

	//Create Closed list
	_ClosedList = new bool[_Width * _Height];
}


Grid::~Grid()
{
	for (int x = 0; x < _Width; x++)
	{
		for (int y = 0; y < _Height; y++)
		{
			delete _NodeList[x][y];
			_NodeList[x][y] = nullptr;
		}
	}

	for (int i = 0; i < _Width; i++)
	{
		delete[] _NodeList[i];
		_NodeList[i] = nullptr; 
	}

	delete[] _NodeList;
	_NodeList = nullptr; 
}

void Grid::Draw(aie::Renderer2D* pRenderer)
{
	for (int x = 0; x < _Width; x++)
	{
		for (int y = 0; y < _Height; y++)
		{
			Vector2 v2Pos = _NodeList[x][y]->_Position;

			pRenderer->setRenderColour(0.2f, 0.2f, 0.2f);

			if (_NodeList[x][y]->_Blocked)
				pRenderer->setRenderColour(0.0f,0.4f,1.0f);

			pRenderer->drawBox(v2Pos.x, v2Pos.y, SQUARE_SIZE - 10.0f, SQUARE_SIZE - 10.0f);
			if (_ToggleLines)
			{
				for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
				{
					if (_NodeList[x][y]->_Neighbours[n])
					{
						Vector2 NeighbourPos = _NodeList[x][y]->_Neighbours[n]->_Position;
						pRenderer->setRenderColour(0.3f, 0.0f, 0.3f);
						pRenderer->drawLine(v2Pos.x, v2Pos.y, NeighbourPos.x, NeighbourPos.y, 2.5f);
					}
				}
			}
		}
	}
}

void Grid::update(float deltaTime, aie::Input* input)
{
	//Toggle neighbour lines
	if (input->wasKeyPressed(aie::INPUT_KEY_G))
	{
		if (_ToggleLines)
			_ToggleLines = false;
		else
			_ToggleLines = true;
	}

	// Clear Nodes
	if (input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		for (int x = 0; x < _Width; x++)
		{
			for (int y = 0; y < _Height; y++)
			{
				_NodeList[x][y]->_Blocked = false;
			}
		}
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		int test = 0;
		for (int x = 0; x < _Width; x++)
		{
			for (int y = 0; y < _Height; y++)
			{
				test = rand() % 10;
	
				if (test < 4)
					_NodeList[x][y]->_Blocked = true;
				else
					_NodeList[x][y]->_Blocked = false;
			}
		}
	}
}

Node* Grid::GetNodeByPos(Vector2 Pos)
{
	int x = (Pos.x - GRID_POSX + (SQUARE_SIZE * 0.5)) / SQUARE_SIZE;
	int y = (Pos.y - GRID_POSY + (SQUARE_SIZE * 0.5)) / SQUARE_SIZE;

	if (x < 0 || y < 0 || x >= _Width || y >= _Height)
		return nullptr;

	return _NodeList[x][y];
}

bool Grid::FindPath(Vector2 Start, Vector2 End, std::vector<Vector2>& path)
{
	// Find start and end nodes
	Node* _StartNode = GetNodeByPos(Start);
	Node* _EndNode = GetNodeByPos(End);
	path.clear();

	if (!_StartNode || !_EndNode)
		return false;
	
	if (_StartNode == _EndNode)
		return false;

	if (_StartNode->_Blocked || _EndNode->_Blocked)
		return false;

	// Make the thingos equal other thingos
	_OpenList.Clear();
	memset(_ClosedList, 0, sizeof(bool) * _Width *_Height);
	bool _FoundPath = false;

	_StartNode->_Prev = nullptr;
	_StartNode->_GScore = 0;
	_StartNode->_HScore = CalculateHeuristic(_StartNode, _EndNode);
	_StartNode->_FScore = _StartNode->_GScore + _StartNode->_HScore;

	_OpenList.Push(_StartNode);

	// Algo Boi
	while (_OpenList.GetCount() > 0)
	{
		// Kill one of the bois
		Node* _Current = _OpenList.Pop();

		// Add to my Boi
		int _Index = _Current->_IndexY * _Width + _Current->_IndexX;
		_ClosedList[_Index] = true;

		// Check if my bois finished, then join him
		if (_Current == _EndNode)
		{
			_FoundPath = true;
			break;
		}

		for (int i = 0; i < NEIGHBOUR_COUNT; i++)
		{
			// Get me Bois
			Node* _Neighbour = _Current->_Neighbours[i];

			// If i got no bois
			if (!_Neighbour)
				continue;

			// If my bois are dead
			if (_Neighbour->_Blocked)
				continue;

			int _NeighbourIndex = _Neighbour->_IndexY * _Width + _Neighbour->_IndexX;
			if (_ClosedList[_NeighbourIndex])
				continue;

			// If the boi has no bois
			if (!_OpenList.Find(_Neighbour))
			{
				_Neighbour->_Prev = _Current;
				_Neighbour->_GScore = _Current->_GScore + _Current->_Costs[i];

				// Calculate the bois networth
				_Neighbour->_HScore = CalculateHeuristic(_Neighbour, _EndNode);
				_Neighbour->_FScore = _Neighbour->_GScore + _Neighbour->_HScore;

				// Introduce a new boi to the bois
				_OpenList.Push(_Neighbour);
			}
			else
			{
				// If there is a better boi replace one of the bois
				int _Cost = _Current->_GScore + _Current->_Costs[i];
				if (_Cost < _Neighbour->_GScore)
				{
					// Ask one of the bois for money for the canteen
					_Neighbour->_GScore = _Cost;

					// My bois networth
					_Neighbour->_FScore = _Neighbour->_GScore + _Neighbour->_HScore;
					_Neighbour->_Prev = _Current;
				}
			}

		}
	}

	if (_FoundPath)
	{
		// Get the final boi
		Node* _Current = _EndNode;

		while (_Current)
		{
			// Line the bois up
			path.insert(path.begin(), _Current->_Position);

			// Bring back one of the old bois
			_Current = _Current->_Prev;
		}
		return true;
	}
	return false;
}

int Grid::CalculateHeuristic(Node * node, Node * _End)
{
	int _DistX = abs(node->_IndexX - _End->_IndexX);
	int _DistY = abs(node->_IndexY - _End->_IndexY);

	if (_DistX > _DistY)
		return (14 * _DistY) + 10 * (_DistX - _DistY);
	else	
		return (14 * _DistX) + 10 * (_DistY - _DistX);
}
