#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include "Input.h"
#include "PathHeap.h"
#include <vector>

class Node;

class Grid
{
public:
	Grid(int Width, int Height, int screenWidth, int screenHeight);
	~Grid();

	void Draw(aie::Renderer2D* Renderer);
	void update(float deltaTime, aie::Input* input);

	Node* GetNodeByPos(Vector2 Pos);
	bool FindPath(Vector2 Start, Vector2 End, std::vector<Vector2>& path);
private:
	bool _ToggleLines;

	Node*** _NodeList;
	
	PathHeap _OpenList;
	bool* _ClosedList;
	
	int _Width;
	int _Height; 
};

