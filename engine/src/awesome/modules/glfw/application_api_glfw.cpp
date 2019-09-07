#include "application_api_glfw.h"

#include "application_glfw.h"
#include "window_glfw.h"

namespace awesome
{
	bool awesome::ApplicationAPI_GLFW::startup()
	{
		return false;
	}
	
	void ApplicationAPI_GLFW::shutdown()
	{
	}
	
	Application* const ApplicationAPI_GLFW::createApplication() const
	{
		return new ApplicationGLFW(const_cast<ApplicationAPI_GLFW*>(this));
	}
	
	Window* const ApplicationAPI_GLFW::createWindow() const
	{
		return new WindowGLFW();
	}
}
