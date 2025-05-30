#include "Quad.h"

Quad::Quad(std::vector<Vertex::vertex> vertices)
{
	this->vertices = vertices;
}

std::vector<Vertex::vertex> Quad::getVertices()
{
	return this->vertices;
}
