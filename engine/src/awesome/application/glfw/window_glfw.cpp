#include "window_glfw.h"

#include <GLFW/glfw3.h>

namespace awesome
{
	WindowGLFW::WindowGLFW()
		: m_windowHandler()
	{

	}

	WindowGLFW::~WindowGLFW()
	{

	}

	bool WindowGLFW::open(const Settings& t_settings)
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
			glfwSetFramebufferSizeCallback(
				m_windowHandler,
				[](GLFWwindow*, int t_width, int t_height)
				{
					//
				}
			);

			return true;
		}
		return false;
	}

	void WindowGLFW::update()
	{
		glfwSwapBuffers(m_windowHandler);
		glfwPollEvents();

		// check for closing window
		if (glfwWindowShouldClose(m_windowHandler))
		{
			m_state = State::Closing;
		}
	}

	void WindowGLFW::setTitle(const std::string& t_title)
	{

	}

	void WindowGLFW::resize(const uint32 t_width, const uint32 t_height)
	{

	}
}