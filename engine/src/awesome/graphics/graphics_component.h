/// Copyright (c) Vito Domenico Tagliente
#pragma once

namespace graphics
{
	class Renderer2D;

	class IGraphicsComponent
	{
	public:
		IGraphicsComponent() = default;
		virtual ~IGraphicsComponent() = default;

		virtual void render(graphics::Renderer2D* const /*renderer*/) = 0;
	};
}