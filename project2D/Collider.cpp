#include "Collider.h"

Collider::Collider(Vector2 v2MinOffset, Vector2 v2MaxOffSet)
{
	_V2Max = v2MaxOffSet;
	_V2Min = v2MinOffset;
}

void Collider::SetPostition(Vector2 v2Pos)
{
	_V2Pos = v2Pos;
}

Vector2 Collider::GetMax()
{
	return _V2Pos + _V2Max;
}

Vector2 Collider::GetMin()
{
	return _V2Pos + _V2Min;
}
