
#include "pch.h"

#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetRenderer(IRenderer* renderer)
{
	m_renderer.push_back(renderer);
}

void Renderer::AllRender()
{
	for (auto& e : m_renderer)
	{
		e->Draw();
	}
}
