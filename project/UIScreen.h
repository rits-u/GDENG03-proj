#pragma once
#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"

#include "GraphicsEngine.h"


typedef std::string String;
class UIManager;

class UIScreen
{
public:
	typedef std::string String;

	UIScreen(String name);
	UIScreen(String name, bool isActive);
	~UIScreen();

	String getName();
	bool isActive();
	void setActive(bool active);
	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	virtual void draw() = 0;
	

protected:
	String name;
	bool activeSelf;
	friend class UIManager;

};

