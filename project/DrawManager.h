#pragma once
#include <vector>
#include "Vertex.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DeviceContext.h"
#include "Quad.h"

class GraphicsEngine;

class DrawManager
{
public:

	static void initialize();
	static DrawManager* getInstance();
	static void destroy();
	int getX();
	//void createQuad(std::vector<Vertex::vertex> vertices);	//store the vertices for a quad, then add it to the list
	//std::vector<Vertex::vertex> getAllQuadVertices();

	void addQuad(const Quad& quad);
	std::vector<Vertex::vertex> combineAllQuadVertices();

	void setUpShadersAndBuffers(VertexBuffer*& vb, ConstantBuffer*& cb, VertexShader*& vs, PixelShader*& ps);
	void updateShadersAndBuffers(VertexBuffer*& vb, ConstantBuffer*& cb, VertexShader*& vs, PixelShader*& ps);
	void drawAllQuads(VertexBuffer*& vb);
	

private: 
	static DrawManager* instance;
	std::vector<Quad> vecQuad;

	DrawManager();
	~DrawManager();
	
private:
	friend class GraphicsEngine;


};

