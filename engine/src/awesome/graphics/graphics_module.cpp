#include "graphics_module.h"

#include <vector>

namespace awesome
{
	GraphicsModule::GraphicsModule(const API t_api)
		: m_api(t_api)
		, m_renderer()
	{
	}

	GraphicsModule::~GraphicsModule()
	{
	}

	bool GraphicsModule::startup_implementation()
	{
		return false;
	}
	
	void GraphicsModule::shutdown_implementation()
	{
	}
	
	void GraphicsModule::update_implementation()
	{
	}
}