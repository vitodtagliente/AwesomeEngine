/// Copyright (c) Vito Domenico Tagliente
#pragma once

namespace graphics
{
	class Renderer2D;
}

class IUIComponent
{
public:
	IUIComponent() = default;
	virtual ~IUIComponent() = default;

	virtual void render(graphics::Renderer2D* const /*renderer*/) = 0;
};