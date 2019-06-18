#pragma once

#include <vector>

struct Node;

class PathHeap
{
public:
	PathHeap();
	~PathHeap();

	void Push(Node* pNode);
	Node* Pop();
	int GetCount();
	void Clear();
	bool Find(Node* _Node);

private:
	int GetParent(int nIndex);
	int GetChild(int nIndex, int nChild);

	std::vector<Node*> _Heap;
};