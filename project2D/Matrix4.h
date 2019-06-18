#pragma once
#include "Vector3.h"
#include "Vector4.h"

struct Matrix4
{
	Matrix4();
	Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);

	Matrix4 operator*(const Matrix4& rhs);
	Vector4 operator*(const Vector4& rhs);

	Vector4& operator[](int index);
	operator float*();

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);



	/*
	X,  Y,  T,  Z
	0,  4,  8,  12
	1,  5,  9,  13
	2,  6,  10, 14
	3,  7,  11, 15
	*/
	float m[16];
};

