#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("RenderSystem not created successfully"); }


	try
	{
		m_texture_manager = new TextureManager();
	}
	catch (...) { throw std::exception("TextureManager not created successfully"); }

}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	try { delete m_texture_manager; }
	catch (...) {}
	try { delete m_render_system; }
	catch (...) {}
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	if(m_render_system)
		return this->m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	if (m_texture_manager)
		return this->m_texture_manager;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine)
		throw std::exception("GraphicsEngine is already created");

	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine)
		return;

	delete GraphicsEngine::m_engine;
}
