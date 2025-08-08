#pragma once
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"

class MyTransform
{
public:
	MyTransform();
	Matrix4x4 getLocalMatrix();

private:
	Matrix4x4 calculateMatrix();

public:
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

