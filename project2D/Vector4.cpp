#include "Vector4.h"
#include <math.h>
#include <cassert>


Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//---------------------------------------
// CROSS
//---------------------------------------

Vector4 Vector4::cross(const Vector4& rhs)
{
	Vector4 result;

	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);
	result.w = 0;

	return result;
}

//---------------------------------------
// NORMALISE
//---------------------------------------

void Vector4::normalise()
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

float Vector4::magnitude()
{
	float result = (x * x) + (y * y) + (z * z);
	return sqrtf(result);
}

float Vector4::magnitudeSqr()
{
	float result = (x * x) + (y * y) + (z * z);
	return result;
}

//---------------------------------------
// DOT
//---------------------------------------

float Vector4::dot(const Vector4& rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

//---------------------------------------
// ARITHMETIC OPERATORS
//---------------------------------------

Vector4 Vector4::operator+(const Vector4& rhs)		// +
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4 Vector4::operator-(const Vector4& rhs)		// -
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4 Vector4::operator*(const float rhs)			// * LEFT
{
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

Vector4 operator*(const float lhs, Vector4 rhs)		// * RIGHT
{
	return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
}

Vector4 Vector4::operator/(const float rhs)			// /
{
	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

//---------------------------------------
// ARITHMETIC EQUALS OPERATORS
//---------------------------------------

Vector4& Vector4::operator+=(const Vector4& rhs)	// +=
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& rhs)	// -=
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;

	return *this;
}

Vector4& Vector4::operator*=(const float rhs)		// *=
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;

	return *this;
}

Vector4& Vector4::operator/=(const float rhs)		// /=
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;

	return *this;
}

//---------------------------------------
// SUBSCRIPT
//---------------------------------------

float& Vector4::operator[](int index)
{
	return *(&x + index);
}

//---------------------------------------
// FLOAT OPERATOR
//-----------------------------------
Vector4::operator float*()
{
	return &x;
}