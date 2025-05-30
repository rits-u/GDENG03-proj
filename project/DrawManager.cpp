#include "DrawManager.h"
#include "GraphicsEngine.h"

DrawManager* DrawManager::instance = nullptr;

int DrawManager::getX()
{
	int x = 100;
	return x;
}

void DrawManager::drawAllQuads(VertexBuffer*& vb)
{
	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);

}

void DrawManager::addQuad(const Quad& quad)
{
	this->vecQuad.push_back(quad);
}

std::vector<Vertex::vertex> DrawManager::combineAllQuadVertices()
{
	std::vector<Vertex::vertex> vertices;
	vertices = this->vecQuad[0].getVertices();

	for (int i = 1; i < this->vecQuad.size(); i++)
	{
		for (Vertex::vertex v : this->vecQuad[i].getVertices())
		{
			vertices.push_back(v);
		}
	}

	return vertices;
}

void DrawManager::setUpShadersAndBuffers(VertexBuffer*& vb, ConstantBuffer*& cb, VertexShader*& vs, PixelShader*& ps)
{
	std::vector<Vertex::vertex> data = DrawManager::getInstance()->combineAllQuadVertices();

	vb = GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);
	UINT size_list = data.size();

	//GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;


	//VERTEX SHADER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//old:
//	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
	vb->load(data.data(), sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);			//vertex buffer

	GraphicsEngine::get()->releaseCompiledShader();


	//PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	Vertex::constant cc;
	cc.m_time = 0;

	//CONSTANT BUFFER
	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(Vertex::constant));


}

void DrawManager::updateShadersAndBuffers(VertexBuffer*& vb, ConstantBuffer*& cb, VertexShader*& vs, PixelShader*& ps)
{
	Vertex::constant cc;
	cc.m_time = ::GetTickCount();
	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);


	//set the default shader in the graphics pipeline to be able to draw
//	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	//set the vertices to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
}

//void DrawManager::createQuad(std::vector<Vertex::vertex> vertices)
//{
//	this->quad_vertices.push_back(vertices);
//}

DrawManager::DrawManager()
{
}

void DrawManager::initialize()
{
	instance = new DrawManager();
}

DrawManager* DrawManager::getInstance()
{
	return instance;
}

void DrawManager::destroy()
{
	delete instance;
}

DrawManager::~DrawManager()
{
}
