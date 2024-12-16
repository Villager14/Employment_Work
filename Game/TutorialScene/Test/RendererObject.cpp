
#include "pch.h"

#include "RendererObject.h"

RendererObject::RendererObject(int i)
	:
	number(i)
{
}

RendererObject::~RendererObject()
{
}

void RendererObject::Initialize()
{
	m_model = ModelMake::Make();
}

void RendererObject::Draw()
{
	//		ƒ‚ƒfƒ‹‚Ì•`‰æ
}