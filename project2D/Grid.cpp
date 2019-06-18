#include "Grid.h"
#include "Node.h"
#include "Vector2.h"
#include <math.h>
#include <iostream>
#include <algorithm>

#define SQUARE_SIZE 25
#define GRID_POSX 10
#define GRID_POSY 10

Grid::Grid(int Width, int Height)
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
				_NodeList[x][y]->_Neighbours[0] = _NodeList[x][y - 1];

			if (x > 0)
				_NodeList[x][y]->_Neighbours[1] = _NodeList[x - 1][y];

			if (y < _Height - 1)
				_NodeList[x][y]->_Neighbours[2] = _NodeList[x][y + 1];

			if (x < _Width - 1)
				_NodeList[x][y]->_Neighbours[3] = _NodeList[x + 1][y];

			_NodeList[x][y]->_Costs[0] = 10;
			_NodeList[x][y]->_Costs[1] = 10;
			_NodeList[x][y]->_Costs[2] = 10;
			_NodeList[x][y]->_Costs[3] = 10;
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
						pRenderer->drawLine(v2Pos.x, v2Pos.y, NeighbourPos.x, NeighbourPos.y, 4.5f);
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
}

Node* Grid::GetNodeByPos(Vector2 Pos)
{
	int x = (Pos.x - GRID_POSX + (SQUARE_SIZE * 0.5)) / SQUARE_SIZE;
	int y = (Pos.y - GRID_POSY + (SQUARE_SIZE * 0.5)) / SQUARE_SIZE;

	if (x < 0 || y < 0 || x >= _Width || y >= _Height)
		return nullptr;

	return _NodeList[x][y];
}

void Grid::SortOpenList()
{
	for (int i = 0; i < _OpenList.size() - 1; ++i)
	{
		for (int j = 0; j < _OpenList.size() - 1 - i; ++j)
		{
			if (_OpenList[j]->_GScore < _OpenList[j + 1]->_GScore)
			{
				Node* _Swap = _OpenList[j];
				_OpenList[j] = _OpenList[j + 1];
				_OpenList[j + 1] = _Swap;
			}
		}
	}
}

bool Grid::FindPath(Vector2 Start, Vector2 End, std::vector<Vector2>& path)
{
	// Find start and end nodes
	Node* _StartNode = GetNodeByPos(Start);
	Node* _EndNode = GetNodeByPos(End);

	if (!_StartNode||!_EndNode)
		return false;
	
	if (_StartNode == _EndNode)
		return false;

	// Make the thingos equal other thingos
	path.clear();
	_OpenList.clear();
	memset(_ClosedList, 0, sizeof(bool) * _Width *_Height);
	bool _FoundPath = false;
	_StartNode->_Prev = nullptr;
	_StartNode->_GScore = 0;
	_OpenList.push_back(_StartNode);

	// Algo Boi
	while (_OpenList.size() > 0)
	{
		// Sort out the bois
		SortOpenList();

		Node* _Current = _OpenList[_OpenList.size() - 1];
		_OpenList.pop_back();

		// Add to my Boi
		int _Index = _Current->_IndexY * _Width + _Current->_IndexX;
		_ClosedList[_Index] = true;

		// Check if my bois finished
		if (_Current == _EndNode)
		{
			_FoundPath = true;
			break;
		}

		for (int i = 0; i < NEIGHBOUR_COUNT; i++)
		{
			Node* _Neighbour = _Current->_Neighbours[i];

			if (!_Neighbour)
				continue;

			if (_Neighbour->_Blocked)
				continue;

			int _NeighbourIndex = _Neighbour->_IndexY * _Width + _Neighbour->_IndexX;
			if (_ClosedList[_NeighbourIndex])
				continue;

			if (std::find(_OpenList.begin(), _OpenList.end(), _Neighbour) == _OpenList.end())
			{

				_Neighbour->_Prev = _Current;
				_Neighbour->_GScore = _Current->_GScore + _Current->_Costs[i];
				_OpenList.push_back(_Neighbour);
			}
			else
			{
				// If there is a better boi replace one of the bois
				int _Cost = _Current->_GScore + _Current->_Costs[i];
				if (_Cost < _Neighbour->_GScore)
				{
					_Neighbour->_GScore = _Cost;
					_Neighbour->_Prev = _Current;
				}
			}

		}
	}

	if (_FoundPath)
	{
		Node* _Current = _EndNode;

		while (_Current)
		{
			path.insert(path.begin(), _Current->_Position);
		}
		return true;
	}
	return false;
}
