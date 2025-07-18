#pragma once

#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh() :m_position(), m_texCoord()
	{

	}

	VertexMesh(Vector3D position, Vector2D texCoord) :m_position(position), m_texCoord(texCoord)
	{

	}

	VertexMesh(const VertexMesh& vertex) :m_position(vertex.m_position), m_texCoord(vertex.m_texCoord)
	{

	}

	~VertexMesh()
	{

	}

public:
	Vector3D m_position;
	Vector2D m_texCoord;
};