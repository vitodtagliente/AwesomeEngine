#include "application_module_glfw.h"

#include "application_glfw.h"
#include "window_glfw.h"

namespace awesome
{
	bool ApplicationModuleGLFW::API_GLFW::startup()
	{
		return true;
	}

	void ApplicationModuleGLFW::API_GLFW::shutdown()
	{

	}

	std::unique_ptr<Application> ApplicationModuleGLFW::API_GLFW::make_application() const
	{
		const ApplicationModule::API& api = dynamic_cast<const ApplicationModule::API&>(*this);
		return std::make_unique<ApplicationGLFW>(api);
	}

	std::unique_ptr<Window> ApplicationModuleGLFW::API_GLFW::make_window() const
	{
		return std::make_unique<WindowGLFW>();
	}
}
