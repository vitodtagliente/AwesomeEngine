/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "core/singleton.h"
#include "math/vector2.h"

#include "camera.h"
#include "common.h"
#include "color.h"
#include "render_target.h"
#include "texture.h"
#include "texture_rect.h"

namespace graphics
{
	class Renderer : public Singleton<Renderer>
	{
	public:
		struct Stats
		{
			int drawCalls{ 0 };
		};

		void submitSetViewport(int width, int height);
		void submitDrawCircle(ShapeRenderStyle style, const math::vec2& position, float radius, const Color& color);
		void submitDrawLine(const math::vec2& point1, const math::vec2& point2, const Color& color);
		void submitDrawRect(ShapeRenderStyle style, const math::vec2& position, float width, float height, const Color& color);
		void submitDrawTexture(Texture& texture, const math::vec2& position, float angle, const math::vec2& scale, const TextureRect& rect = {}, TextureFlipMode flip = TextureFlipMode::None, const Color& color = Color::White);
		void submitDrawTexture(Texture& texture, const TextureRect& rect = {}, const Color& color = Color::White);

		Camera camera;
		graphics::Color color;
		int pixelsPerUnit{ 32 };
		Stats stats;

	private:
		math::vec2 m_viewport;
	};
}