#pragma once
#include "Component.h"
#include "GraphicsEngine.h"

class Renderer : public Component
{
public:
	inline Renderer() : Component(ComponentType::RENDERER) {}

	virtual void init(int width, int height) {};
	virtual void setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list) = 0;
	virtual void update(constant cc, int width, int height, int camIndex) = 0;
	virtual void draw() = 0;

	inline TexturePtr getTexture() { return this->texture; }
	inline void setTexture(std::string texName) {

		//	std::vector<std::string> items = { "Brick", "Wood", "Grass", "Ground", "Sand", "Wall"};
		if (texName == "Brick") {
			texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
			hasTexture = true;
		}
		else if (texName == "Wood") {
			texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
			hasTexture = true;
		}
		else if (texName == "Grass") {
			texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\grass.jpg");
			hasTexture = true;
		}
		else if (texName == "Ground") {
			texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\ground.jpg");
			hasTexture = true;
		}
		else if (texName == "Sand") {
			texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\sand.jpg");
			hasTexture = true;
		}
		else if (texName == "Wall") {
			texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wall.jpg");
			hasTexture = true;
		}
		else if (texName == "None") {
			hasTexture = false;
		}

		this->texName = texName;
	}

	//inline void setTexture()



public:
	bool hasTexture = false;
	bool enableTextureSelection = false;
	std::string texName;

private:
	TexturePtr texture;
	
};

