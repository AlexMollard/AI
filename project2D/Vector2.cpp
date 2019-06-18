#include "Vector2.h"
#include "math.h"
#include <cassert>


Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

//---------------------------------------
// MAGNITUDE
//---------------------------------------

float Vector2::magnitude()
{
	float result = (x * x) + (y * y);
	return sqrtf(result);
}

float Vector2::magnitudeSqr()
{
	float result = (x * x) + (y * y);
	return result;
}

//---------------------------------------
// NORMALISE
//---------------------------------------

void Vector2::normalise()
{
	if (x == 0)
		x = 1;

	if (y == 0)
		y = 1;

	float mag = magnitude();

	if (mag == 0)
		mag = 1.0f;

	_STL_ASSERT(mag != 0.0f, "- Normalise: Divided by zero -");

	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
	}
}

//---------------------------------------
// DOT
//---------------------------------------

float Vector2::dot(const Vector2& rhs)
{
	return (x * rhs.x) + (y * rhs.y);
}

//---------------------------------------
// DIRECTION	( RIGHT / LEFT )
//---------------------------------------

Vector2 Vector2::right()
{
	return Vector2(-y, x);
}

Vector2 Vector2::left()
{
	return Vector2(y, -x);
}

//---------------------------------------
// ARITHMETIC OPERATORS
//---------------------------------------

Vector2 Vector2::operator+(const Vector2& rhs)		// +
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs)		// -
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const float rhs)			// * LEFT
{
	return Vector2(x * rhs, y * rhs);
}

Vector2 operator*(const float lhs, Vector2 rhs)		// * RIGHT
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

Vector2 Vector2::operator/(const float rhs)			// /
{
	return Vector2(x / rhs, y / rhs);
}

//---------------------------------------
// ARITHMETIC EQUALS OPERATORS
//---------------------------------------

Vector2& Vector2::operator+=(const Vector2& rhs)	// +=
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)	// -=
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vector2& Vector2::operator*=(const float rhs)		// *=
{
	x *= rhs;
	y *= rhs;

	return *this;
}

Vector2& Vector2::operator/=(const float rhs)		// /=
{
	x /= rhs;
	y /= rhs;

	return *this;
}

//---------------------------------------
// SUBSCRIPT
//---------------------------------------

float& Vector2::operator[](int index)
{
	return *(&x + index);
}

//---------------------------------------
// FLOAT OPERATOR
//---------------------------------------

Vector2::operator float*()
{
	return &x;
}