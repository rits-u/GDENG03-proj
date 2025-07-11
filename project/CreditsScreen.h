#pragma once
#include "UIScreen.h"

class CreditsScreen : public UIScreen
{
public:
	CreditsScreen();
	~CreditsScreen();

	void draw() override;

private:
	int imageWidth;
	int imageHeight;
	//bool isActive;
	ID3D11ShaderResourceView* myTexture;
};

