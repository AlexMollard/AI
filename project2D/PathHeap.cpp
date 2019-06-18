#include "PathHeap.h"
#include "Node.h"
#include <algorithm>

PathHeap::PathHeap()
{

}

PathHeap::~PathHeap()
{

}

void PathHeap::Push(Node* pNode)
{
	_Heap.push_back(pNode);

	int _Current = _Heap.size() - 1;
	int _Parent = GetParent(_Current);

	while (_Heap[_Current]->_GScore < _Heap[_Parent]->_GScore)
	{
		Node* _Swap = _Heap[_Current];
		_Heap[_Current] = _Heap[_Parent];
		_Heap[_Parent] = _Swap;

		_Current = _Parent;
		_Parent = GetParent(_Current);
	}
}

Node* PathHeap::Pop()
{
	Node* _Node = _Heap[0];
	int _Last = _Heap.size() - 1;
	int _Current = 0;
	_Heap[0] = _Heap[_Last];
	_Heap.pop_back();

	int _Child1Index = GetChild(_Current, 1);
	int _Child2Index = GetChild(_Current, 2);

	int _CheapestIndex = _Child1Index;
	if (_CheapestIndex >= _Heap.size())
		return _Node;

	if (_Child2Index < _Heap.size() && _Heap[_Child2Index]->_GScore < _Heap[_CheapestIndex]->_GScore)
		_CheapestIndex = _Child2Index;

	while (_Heap[_CheapestIndex]->_GScore < _Heap[_Current]->_GScore)
	{
		Node* _Swap = _Heap[_CheapestIndex];
		_Heap[_CheapestIndex] = _Heap[_Current];
		_Heap[_Current] = _Swap;

		_Current = _CheapestIndex;
		_Child1Index = GetChild(_Current, 1);
		_Child2Index = GetChild(_Current, 2);

		_CheapestIndex = _Child1Index;
		if (_CheapestIndex >= _Heap.size())
			return _Node;

		if (_Child2Index < _Heap.size() && _Heap[_Child2Index]->_GScore < _Heap[_CheapestIndex]->_GScore)
			_CheapestIndex = _Child2Index;
	}
	return _Node;
}

int PathHeap::GetParent(int nIndex)
{
	return (nIndex - 1) / 2;
}

int PathHeap::GetChild(int nIndex, int nChild)
{
	return (2 * nIndex) + nChild;
}

int PathHeap::GetCount()
{
	return _Heap.size();
}

void PathHeap::Clear()
{
	_Heap.clear();
}

bool PathHeap::Find(Node* _Node)
{
	return std::find(_Heap.begin(), _Heap.end(), _Node) != _Heap.end();
}
