#include <awesome/platform.h>

#ifdef PLATFORM_DESKTOP

#include <awesome/core/window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <awesome/core/input.h>
#include <awesome/core/log.h>

// Desktop OS window management using GLFW

namespace awesome
{
	void Window::platformClear()
	{

	}
	
	bool Window::platformOpen()
	{
		if (!glfwInit()) {
			log(LogSeverity::Engine, "Cannot initialize GLFW");
			return false;
		}

		log(LogSeverity::Engine, "Windowing...");
		m_WindowHandler = glfwCreateWindow(
			m_Properties.width,
			m_Properties.height,
			m_Title.c_str(), nullptr, nullptr 
		);

		if (!m_WindowHandler) {
			log(LogSeverity::Engine, "Cannot create GLFW context");
			return false;
		}

		glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_WindowHandler));

		glfwSetFramebufferSizeCallback(
			static_cast<GLFWwindow*>(m_WindowHandler), 
			[](GLFWwindow* /*context*/, const int width, const int height
		){
			//glViewport(0, 0, width, height);
		});

		return true;
	}

	void Window::platformUpdate()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_WindowHandler));
		glfwPollEvents();

		// check for closing window
		if (glfwWindowShouldClose(static_cast<GLFWwindow*>(m_WindowHandler)))
		{
			m_State = WindowState::Closing;
		}
	}

	void Window::setTitle(const std::string& title)
	{
		m_Title = title;
		glfwSetWindowTitle(static_cast<GLFWwindow*>(m_WindowHandler), title.c_str());
	}

	void Window::resize(const uint32 width, const uint32 height) 
	{
		m_Properties.width = width;
		m_Properties.height = height;
		glfwSetWindowSize(static_cast<GLFWwindow*>(m_WindowHandler), width, height);
	}
}

#endif 