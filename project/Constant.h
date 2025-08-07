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
	float useTexture;
	float padding[2];
	//Vector4D wireColor;
};