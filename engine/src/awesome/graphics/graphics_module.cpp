#include "graphics_module.h"

namespace awesome
{
	GraphicsModule::GraphicsModule()
		: m_api(API::Null)
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