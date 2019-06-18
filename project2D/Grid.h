#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include "Input.h"

class Node;

class Grid
{
public:
	Grid(int Width, int Height);
	~Grid();

	void Draw(aie::Renderer2D* Renderer);
	void update(float deltaTime, aie::Input* input);

	Node* GetNodeByPos(Vector2 Pos);
	bool FindPath(Vector2 Start, Vector2 End, std::vector<Vector2>& path);
	void SortOpenList();
private:
	bool _ToggleLines;

	Node*** _NodeList;
	
	std::vector<Node*> _OpenList;
	bool* _ClosedList;
	
	int _Width;
	int _Height; 
};

