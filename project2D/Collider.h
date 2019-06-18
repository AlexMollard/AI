#pragma once
#include "Vector2.h"

class Collider
{
public:
	Collider(Vector2 v2MinOffset, Vector2 v2MaxOffSet);

	void SetPostition(Vector2 v2Pos);

	Vector2 GetMax();
	Vector2 GetMin();

private:
	Vector2 _V2Pos;
	Vector2 _V2Max;
	Vector2 _V2Min;
};

