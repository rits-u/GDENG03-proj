#include "Renderer.h"

Renderer::Renderer() : Component(ComponentType::RENDERER) {}

TexturePtr Renderer::getTexture()
{
	return this->texture;
}

void Renderer::setTexture(std::string texName) {

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

float Renderer::getSize()
{
	return this->size;
}

void Renderer::setSize(float size)
{
	this->size = size;
}

float Renderer::getRadius()
{
	return this->radius;
}

void Renderer::setRadius(float radius)
{
	this->radius = radius;
}

