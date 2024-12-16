#pragma once

#include "IRenderer.h"

class Renderer
{
public:

	Renderer();

	~Renderer();

	void SetRenderer(IRenderer* renderer);

	//		‚·‚×‚Ä•`‰æ
	void AllRender();

private:

	std::vector<IRenderer*> m_renderer;
};