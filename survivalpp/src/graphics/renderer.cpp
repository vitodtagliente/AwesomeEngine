#include "renderer.h"

namespace graphics
{
	void Renderer::init(Context* const context)
	{
		m_context = context;
		primitives = std::make_unique<PrimitiveBatch>(context);
		sprites = std::make_unique<SpriteBatch>(context);
		text = std::make_unique<TextBatch>(context);
	}

	void Renderer::begin()
	{
		m_context->clear(color);
	}

	void Renderer::flush()
	{
		primitives->flush();
		sprites->flush();
		text->flush();

		stats.draw_calls = primitives->stats().draw_calls
			+ sprites->stats().draw_calls
			+ text->stats().draw_calls;
	}

	math::vec2 Renderer::screenToWorld(const math::vec2& position)
	{
		return math::vec2();
	}
}