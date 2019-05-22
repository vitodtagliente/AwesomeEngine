#include "graphics_module.h"

namespace awesome
{
	GraphicsModule::GraphicsModule(const API t_api)
		: m_api(t_api)
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