
#pragma once

#include "IRenderer.h"

#include "ModelMake.h"

class RendererObject : public IRenderer, public ModelMake
{
public:

	RendererObject(int i);

	~RendererObject();

	void Initialize();

	void Draw() override;

private:

	int number;

	//		ƒ‚ƒfƒ‹
	std::unique_ptr<DirectX::Model> m_model;
};