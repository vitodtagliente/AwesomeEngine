#include <awesome/core/window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace awesome
{
	bool Window::platformOpen(const Settings& t_settings)
	{
		// #todo: should be called only one time
		if (!glfwInit())
		{
			// cannot initialize glfw
			return false;
		}

		m_windowHandler = glfwCreateWindow(
			t_settings.width,
			t_settings.height,
			t_settings.title.c_str(),
			false, false
		);

		if (m_windowHandler != nullptr)
		{
			glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_windowHandler));

			// resize callback
			glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(m_windowHandler), 
				[](GLFWwindow*, int t_width, int t_height) 
				{
					glViewport(0, 0, t_width, t_height);
				}
			);

			return true;
		}
		return false;
	}

	void Window::platformUpdate()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_windowHandler));
		glfwPollEvents();

		// check for closing window
		if (glfwWindowShouldClose(static_cast<GLFWwindow*>(m_windowHandler)))
		{
			// #todo: closing event
			m_state = State::Closing;
		}
	}

	void Window::setTitle(const std::string& t_title)
	{

	}

	void Window::resize(const uint32 t_width, const uint32 t_height)
	{

	}
}