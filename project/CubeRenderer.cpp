#include "CubeRenderer.h"
#include "GraphicsEngine.h"

VertexBufferPtr CubeRenderer::sharedVB = nullptr;
IndexBufferPtr CubeRenderer::sharedIB = nullptr;

CubeRenderer::CubeRenderer() : Component(ComponentType::RENDERER)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	
	Vector3D positionList[] =
	{
		//CUBE
		//front face
		{ Vector3D(-0.5f, -0.5f, -0.5f)},		//pos1
		{ Vector3D(-0.5f, 0.5f, -0.5f) },		//pos2
		{ Vector3D(0.5f, 0.5f, -0.5f)  },		//pos3
		{ Vector3D(0.5f, -0.5f, -0.5f) },		//pos4

		//back face
		{ Vector3D(0.5f, -0.5f, 0.5f) },		//pos5
		{ Vector3D(0.5f, 0.5f, 0.5f)  },		//pos6
		{ Vector3D(-0.5f, 0.5f, 0.5f) },		//pos7
		{ Vector3D(-0.5f, -0.5f, 0.5f)},		//pos8
	};

	Vector2D texCoordList[] =
	{
		{ Vector2D(0.0f, 0.0f) },		//pos1
		{ Vector2D(0.0f, 1.0f) },		//pos2
		{ Vector2D(1.0f, 0.0f) },		//pos3
		{ Vector2D(1.0f, 1.0f) },		//pos4
	};

	vertex vertex_list[] =
	{
		//front face
		{ positionList[0], texCoordList[1] },
		{ positionList[1], texCoordList[0] },
		{ positionList[2], texCoordList[2] },
		{ positionList[3], texCoordList[3] },

		//back face
		{ positionList[4], texCoordList[1] },
		{ positionList[5], texCoordList[0] },
		{ positionList[6], texCoordList[2] },
		{ positionList[7], texCoordList[3] },

		{ positionList[1], texCoordList[1] },
		{ positionList[6], texCoordList[0] },
		{ positionList[5], texCoordList[2] },
		{ positionList[2], texCoordList[3] },

		{ positionList[7], texCoordList[1] },
		{ positionList[0], texCoordList[0] },
		{ positionList[3], texCoordList[2] },
		{ positionList[4], texCoordList[3] },

		{ positionList[3], texCoordList[1] },
		{ positionList[2], texCoordList[0] },
		{ positionList[5], texCoordList[2] },
		{ positionList[4], texCoordList[3] },

		{ positionList[7], texCoordList[1] },
		{ positionList[6], texCoordList[0] },
		{ positionList[1], texCoordList[2] },
		{ positionList[0], texCoordList[3] },

	};

	unsigned int index_list[] =
	{
		//front side
		0, 1, 2,	//first triangle
		2, 3, 0,	//2nd

		//back side
		4, 5, 6,	//3rd
		6, 7, 4,	//4th

		//top side
		8, 9, 10,
		10, 11, 8,

		//bottom side
		12, 13, 14,
		14, 15, 12,

		//right side
		16, 17, 18,
		18, 19, 16,

		//left side
		20, 21, 22,
		22, 23, 20
	};

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	UINT size_list = ARRAYSIZE(vertex_list);
	sharedVB = renderSystem->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	UINT size_index_list = ARRAYSIZE(index_list);
	sharedIB = renderSystem->createIndexBuffer(index_list, size_index_list, renderSystem);


}

void CubeRenderer::update(constant cc)
{
	draw();
}

void CubeRenderer::release()
{
}

void CubeRenderer::draw()
{

}