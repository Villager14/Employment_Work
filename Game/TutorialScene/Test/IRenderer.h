
#pragma once

class IRenderer
{
public:

	virtual ~IRenderer() = default;

	virtual void Draw() = 0;
};