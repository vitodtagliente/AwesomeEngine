#include "canvas.h"

#include <GLFW/glfw3.h>

#include "input.h"
#include "keycode.h"

Canvas::Canvas()
	: m_handler()
	, m_width()
	, m_height()
	, m_isOpen(false)
{
}

bool Canvas::open(Settings settings)
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* const handler = glfwCreateWindow(
		settings.width,
		settings.height,
		settings.title.c_str(),
		false,
		false
	);

	if (handler == nullptr)
	{
		return false;
	}

	glfwMakeContextCurrent(handler);
	m_width = settings.width;
	m_height = settings.height;
	m_isOpen = true;

	glfwSetKeyCallback(
		handler,
		[](GLFWwindow*, const int key, const int, const int action, const int)
		{
			auto key_state = KeyState::Down;
			if (action == GLFW_PRESS)
			{
				key_state = KeyState::Pressed;
			}
			else if (action == GLFW_RELEASE)
			{
				key_state = KeyState::Released;
			}

			Input::instance().setKeyState(key, key_state);
		}
	);

	glfwSetMouseButtonCallback(
		handler,
		[](GLFWwindow*, const int button, const int action, int)
		{
			auto key_state = KeyState::Down;
			if (action == GLFW_PRESS)
			{
				key_state = KeyState::Pressed;
			}
			else if (action == GLFW_RELEASE)
			{
				key_state = KeyState::Released;
			}

			Input::instance().setKeyState(button, key_state);
		}
	);

	glfwSetCursorPosCallback(
		handler,
		[](GLFWwindow*, const double x, const double y)
		{
			Input::instance().setMousePosition(static_cast<float>(x), static_cast<float>(y));
		}
	);

	glfwSetCursorEnterCallback(
		handler,
		[](GLFWwindow*, const int entered)
		{
			Input::instance().setMousePositionValid(entered);
		}
	);

	// mouse wheel
	glfwSetScrollCallback(
		handler,
		[](GLFWwindow*, const double xoffset, const double yoffset)
		{
			Input::instance().setMouseWheelPosition(static_cast<float>(xoffset), static_cast<float>(yoffset));
		}
	);


	m_handler = reinterpret_cast<void*>(handler);
	return true;
}

void Canvas::update()
{
	if (GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler))
	{
		glfwPollEvents();

		// get the size of the window
		glfwGetWindowSize(handler, &m_width, &m_height);

		// check for closing window
		if (glfwWindowShouldClose(handler))
		{
			m_isOpen = false;
		}
		glfwSwapBuffers(handler);
	}
}

void Canvas::close()
{
	if (GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler))
	{
		glfwSetWindowShouldClose(handler, true);
	}
}

void Canvas::maximize()
{
	if (GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler))
	{
		glfwMaximizeWindow(handler);
	}
}

void Canvas::resize(unsigned int width, unsigned int height)
{
	if (GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler))
	{
		glfwSetWindowSize(handler, static_cast<int>(width), static_cast<int>(height));
	}
}

void Canvas::setTitle(const std::string& title)
{
	if (GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler))
	{
		glfwSetWindowTitle(handler, title.c_str());
	}
}