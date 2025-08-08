#pragma once
#include "Component.h"
#include "GraphicsEngine.h"
#include "TextureManager.h"

class Renderer : public Component
{
public:
	Renderer();

	virtual void init(int width, int height) {};
	virtual void setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list) = 0;
	virtual void update(constant cc, int width, int height, int camIndex) = 0;
	virtual void draw() = 0;

	TexturePtr getTexture();
	void setTexture(std::string texName);

	float getSize();
	void setSize(float size);

	float getRadius();
	void setRadius(float radius);

public:
	bool hasTexture = false;
	bool enableTextureSelection = false;
	std::string texName;

private:
	TexturePtr texture;
	float size;
	float radius;
	
};

