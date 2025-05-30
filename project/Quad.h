#pragma once
#include "Vertex.h"

#include <vector>

class Quad
{
public:
	Quad(std::vector<Vertex::vertex> vertices);
	std::vector<Vertex::vertex> getVertices();

private:
	std::vector<Vertex::vertex> vertices;
};

