#include "window_glfw.h"

#include <GLFW/glfw3.h>

namespace awesome
{
	WindowGLFW::WindowGLFW()
		: m_windowHandler()
	{

	}

	bool WindowGLFW::open_implementation(const Settings& t_settings)
	{
		m_windowHandler = glfwCreateWindow(
			t_settings.width,
			t_settings.height,
			t_settings.title.c_str(),
			false, false
		);

		if (m_windowHandler != nullptr)
		{
			glfwMakeContextCurrent(m_windowHandler);

			// resize callback
			/*
			glfwSetFramebufferSizeCallback(
				m_windowHandler,
				[](GLFWwindow*, int t_width, int t_height)
				{
					//
				}
			);
			*/

			return true;
		}
		return false;
	}

	void WindowGLFW::close_implementation()
	{

	}

	void WindowGLFW::update_implementation()
	{
		glfwSwapBuffers(m_windowHandler);
		glfwPollEvents();

		// check for closing window
		if (glfwWindowShouldClose(m_windowHandler))
		{
			// #todo
			m_isOpen = false;
		}
	}

	void WindowGLFW::setTitle(const std::string& t_title)
	{
		glfwSetWindowTitle(m_windowHandler, t_title.c_str());
	}

	void WindowGLFW::resize(const uint32 t_width, const uint32 t_height)
	{
		glfwSetWindowSize(m_windowHandler, t_width, t_height);
	}
}