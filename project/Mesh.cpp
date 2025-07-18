#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "GraphicsEngine.h"
#include "VertexMesh.h"
#include "InputSystem.h"

Mesh::Mesh(const wchar_t* fullPath) : Resource(fullPath)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warning;
	std::string error;

//	std::string inputFile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(fullPath);
	std::string inputFile = WStringToString(fullPath);


	bool res = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, inputFile.c_str());

	if (!error.empty()) {
		throw std::exception("Mesh not created successfully");
	}

	if (!res) {
		throw std::exception("Mesh not created successfully");
	}

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");


	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;


	for (size_t s = 0; s < shapes.size(); s++) {
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
			
			for (unsigned char v = 0; v < num_face_verts; v++) {
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attributes.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attributes.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attributes.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attributes.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attributes.texcoords[index.texcoord_index * 2 + 1];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back(index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	vertexBuffer = renderSystem->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);

	indexBuffer = renderSystem->createIndexBuffer(&list_indices[0], (UINT)list_indices.size(), renderSystem);



}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return vertexBuffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return indexBuffer;
}

std::string Mesh::WStringToString(const std::wstring& wstr)
{
	if (wstr.empty()) return {};

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string strTo(size_needed - 1, 0); // exclude null terminator
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &strTo[0], size_needed, nullptr, nullptr);
	return strTo;
}
