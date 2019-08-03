#include "application_api_glfw.h"

#include "application_glfw.h"
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
	
	Application* const ApplicationAPI_GLFW::createApplication() const
	{
		return new ApplicationGLFW(const_cast<ApplicationAPI_GLFW*>(this));
	}

	Input* const ApplicationAPI_GLFW::createInput() const
	{
		return new InputGLFW();
	}
	
	Time* const ApplicationAPI_GLFW::createTime() const
	{
		return new TimeGLFW();
	}
	
	Window* const ApplicationAPI_GLFW::createWindow() const
	{
		return new WindowGLFW();
	}
}
