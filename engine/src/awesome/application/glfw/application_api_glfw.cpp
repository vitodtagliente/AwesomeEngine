#include "application_api_glfw.h"

#include "input_glfw.h"
#include "time_glfw.h"
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
	
	Input* ApplicationAPI_GLFW::createInput() const
	{
		return new InputGLFW();
	}
	
	Time* ApplicationAPI_GLFW::createTime() const
	{
		return new TimeGLFW();
	}
	
	Window* ApplicationAPI_GLFW::createWindow() const
	{
		return new WindowGLFW();
	}
}
