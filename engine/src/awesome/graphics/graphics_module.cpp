#include "graphics_module.h"

#include "context.h"

namespace graphics
{
	void Module::startup()
	{

	}

	void Module::shutdown()
	{
	}

	void Module::preRendering()
	{
		Context::instance().renderer.begin();
	}

	void Module::postRendering()
	{
		Context& context = Context::instance();
		context.m_drawCalls = context.renderer.flush();
	}
}