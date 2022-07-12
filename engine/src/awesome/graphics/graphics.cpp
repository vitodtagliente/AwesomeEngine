#include "graphics.h"

#include "context.h"

namespace graphics
{
	void Graphics::startup()
	{

	}

	void Graphics::shutdown()
	{
	}

	void Graphics::preRendering()
	{
		Context::instance().renderer.begin();
	}

	void Graphics::postRendering()
	{
		Context& context = Context::instance();
		context.m_drawCalls = context.renderer.flush();
	}
}