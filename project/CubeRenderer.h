#pragma once
#include "Component.h"
#include "Prerequisites.h"

class CubeRenderer : public Component
{
public:
	CubeRenderer();

	void update(constant cc) override;
	void release() override;

private:
	void draw();

private:
	static VertexBufferPtr sharedVB;
	static PixelShaderPtr sharedPS;
	static IndexBufferPtr sharedIB;
	TexturePtr texture;
	ConstantBufferPtr cb;

};