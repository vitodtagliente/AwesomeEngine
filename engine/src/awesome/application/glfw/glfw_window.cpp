#include "glfw_window.h"

#include <GLFW/glfw3.h>

namespace awesome
{
	GLFWWindow::GLFWWindow()
		: m_windowHandler()
	{

	}

	GLFWWindow::~GLFWWindow()
	{

	}

	bool GLFWWindow::open(const Settings& t_settings)
	{

	}

	void GLFWWindow::update()
	{
		glfwSwapBuffers(m_windowHandler);
		glfwPollEvents();

		// check for closing window
		if (glfwWindowShouldClose(m_windowHandler))
		{
			m_state = State::Closing;
		}
	}

	void GLFWWindow::setTitle(const std::string& t_title)
	{

	}

	void GLFWWindow::resize(const uint32 t_width, const uint32 t_height)
	{

	}
}