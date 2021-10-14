#include "graphics.h"

#include <glad/glad.h>

namespace graphics
{
	Graphics::Graphics()
		: m_context(nullptr)
		, m_renderer(nullptr)
	{
	}

	void Graphics::startup()
	{
		gladLoadGL();
		m_context = new Context();
		m_renderer = new Renderer(*m_context);
	}

	void Graphics::shutdown()
	{
		delete m_renderer;
		delete m_context;
	}

	void Graphics::preRendering()
	{
		m_renderer->begin();
	}

	void Graphics::render(graphics::Renderer* const renderer)
	{
	}

	void Graphics::postRendering()
	{
		m_renderer->flush();
	}
}