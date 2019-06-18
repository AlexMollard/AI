#include "Vector3.h"
#include <math.h>
#include <cassert>


Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//---------------------------------------
// CROSS
//---------------------------------------

Vector3 Vector3::cross(const Vector3& rhs)
{
	Vector3 result;

	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);

	return result;
}

//---------------------------------------
// NORMALISE
//---------------------------------------

void Vector3::normalise()
{
	float mag = magnitude();

	_STL_ASSERT(mag != 0.0f, "- Normalise: Divided by zero -");

	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

//---------------------------------------
// MAGNITUDE
//---------------------------------------

float Vector3::magnitude()
{
	float result = (x * x) + (y * y) + (z * z);
	return sqrtf(result);
}

float Vector3::magnitudeSqr()
{
	float result = (x * x) + (y * y) + (z * z);
	return result;
}

//---------------------------------------
// DOT
//---------------------------------------

float Vector3::dot(const Vector3& rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

//---------------------------------------
// ARITHMETIC OPERATORS
//---------------------------------------

Vector3 Vector3::operator+(const Vector3& rhs)		// +
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3& rhs)		// -
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator*(const float rhs)			// * LEFT
{
	return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3 operator*(const float lhs, Vector3 rhs)		// * RIGHT
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vector3 Vector3::operator/(const float rhs)			// /
{
	return Vector3(x / rhs, y / rhs, z / rhs);
}

//---------------------------------------
// ARITHMETIC EQUALS OPERATORS
//---------------------------------------

Vector3& Vector3::operator+=(const Vector3& rhs)	// +=
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)	// -=
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vector3& Vector3::operator*=(const float rhs)		// *=
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

Vector3& Vector3::operator/=(const float rhs)		// /=
{
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

//---------------------------------------
// SUBSCRIPT
//---------------------------------------

float& Vector3::operator[](int index)
{
	return *(&x + index);
}

//---------------------------------------
// FLOAT OPERATOR
//-----------------------------------
Vector3::operator float*()
{
	return &x;
}