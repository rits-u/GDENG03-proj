#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "InputListener.h"
#include "Point.h"

#include "Cube.h"
#include "Plane.h"
#include "Circle.h"
#include "Camera.h"

#include <iostream>
#include <vector>
#include <random>

//#include "IMGUI/imgui.h"
//#include "IMGUI/imgui_impl_dx11.h"
//#include "IMGUI/imgui_impl_win32.h"

#include "UIManager.h"
#include "GameObjectManager.h"

#include "Types.h"

//#define _CRT_SECURE_NO_WARNINGS
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mousePos) override;
	virtual void onLeftMouseDown(const Point& mousePos) override;
	virtual void onLeftMouseUp(const Point& mousePos) override;
	virtual void onRightMouseDown(const Point& mousePos) override;
	virtual void onRightMouseUp(const Point& mousePos) override;

private:
	float generateRandomFloat(float min, float max);
	void spawnCircle(void* shader_byte_code, size_t size_shader);
	float convertToRadians(float degrees);
	Vector3D convertPixelsToWorld(float scale, float px, float py, float width, float height);
	void createCamera(Layer layer, float depth, bool enabled);
	//void createGameObjects(GameObject obj, int num, float scale, Layer layer, )

private:
	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

public:
	//Cube* cubeObject;
	//Camera* camera;

private:
	SwapChainPtr m_swap_chain;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	TexturePtr woodTex;
	MeshPtr mesh;

	void* VS_ShaderByteCode = nullptr;
	size_t VS_SizeShader = 0;
	void* PS_ShaderByteCode = nullptr;
	size_t PS_SizeShader = 0;
	bool holding = false;

	void* mesh_ShaderByteCode = nullptr;
	size_t mesh_SizeShader = 0;
	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;

private:
	std::vector<Cube*> cubeList;
	std::vector<Plane*> planeList;
	std::vector<Circle*> circleList;
	std::vector<GameObject*> UIElements;
	std::vector<Camera*> sortedCameras;


private:
	bool test = true;

private:
	/*	my_image_texture
		my_image_width
		my_image_height*/

};

