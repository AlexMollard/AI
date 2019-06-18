#pragma once
#include "Vector3.h"
#include "Vector2.h"

struct Matrix3
{
	Matrix3();
	Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);

	Matrix3 operator*(const Matrix3& rhs);
	Vector3 operator*(const Vector3& rhs);

	Vector3& operator[](int index);
	operator float*();

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setPostion(float x, float y);
	void setPostion(Vector2 pos);

	void SetTranslation(Vector2 v2Pos);
	Vector2 GetTranslation();

	void setScale(float x, float y);
	void setScale(Vector2 scale);

	Vector2 getPosition();
	float getRotation();
	void setRotation(float rotation);
	Vector2 getScale();

	/*
	X, Y, T
	0, 3, 6
	1, 4, 7
	2, 5, 8
	*/
	float m[9];
	float rotation;
	Vector2 scale;
};