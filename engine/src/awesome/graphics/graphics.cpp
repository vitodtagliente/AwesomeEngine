#include "graphics.h"

#include <glad/glad.h>

namespace graphics
{
	void Graphics::startup()
	{
		gladLoadGL();
		Renderer::instance();
	}

	void Graphics::shutdown()
	{
	}

	void Graphics::preRendering()
	{
		Renderer::instance().begin();
	}

	void Graphics::render(graphics::Renderer* const)
	{
	}

	void Graphics::postRendering()
	{
		Renderer::instance().flush();
	}
}