/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <vdtgraphics/graphics.h>

#include "core/singleton.h"
#include "math/vector2.h"

#include "common.h"
#include "color.h"
#include "texture.h"
#include "texture_rect.h"

namespace graphics
{
	class Renderer : public Singleton<Renderer>
	{
	public:
		struct Stats
		{
			int draw_calls{ 0 };
		};

		void init(Context* const context);
		
		void begin();
		void flush();

		math::vec2 screenToWorld(const math::vec2& position);

		Camera camera;
		graphics::Color color;
		int pixelsPerUnit{ 32 };
		Stats stats;

		std::unique_ptr<PrimitiveBatch> primitives;
		std::unique_ptr<SpriteBatch> sprites;
		std::unique_ptr<TextBatch> text;

	private:
		Context* m_context{ nullptr };
	};
}