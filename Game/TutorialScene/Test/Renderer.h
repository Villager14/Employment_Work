#pragma once

#include "IRenderer.h"

class Renderer
{
public:

	Renderer();

	~Renderer();

	void SetRenderer(IRenderer* renderer);

	//		���ׂĕ`��
	void AllRender();

private:

	std::vector<IRenderer*> m_renderer;
};