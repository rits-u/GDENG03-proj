#pragma once
#include "Matrix4x4.h"
#include "Vector4D.h"

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float useWireColor;
	float padding[3]; // for 16-byte alignment
	Vector4D wireColor;

};