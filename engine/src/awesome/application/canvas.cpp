#include "canvas.h"

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

	// resize callback
	glfwSetFramebufferSizeCallback(handler, Canvas::handleResize);

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

			if (Input* const input = Input::instance())
			{
				input->setKeyState(key, key_state);
			}
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

			if (Input* const input = Input::instance())
			{
				input->setKeyState(button, key_state);
			}
		}
	);

	glfwSetCursorPosCallback(
		handler,
		[](GLFWwindow*, const double x, const double y)
		{
			if (Input* const input = Input::instance())
			{
				input->setMousePosition(static_cast<float>(x), static_cast<float>(y));
			}
		}
	);

	glfwSetCursorEnterCallback(
		handler,
		[](GLFWwindow*, const int entered)
		{
			if (Input* const input = Input::instance())
			{
				input->setMousePositionValid(entered);
			}
		}
	);

	m_handler = reinterpret_cast<void*>(handler);
	return true;
}

void Canvas::update()
{
	glfwPollEvents();

	// check for closing window
	GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler);
	if (glfwWindowShouldClose(handler))
	{
		m_isOpen = false;
	}
	glfwSwapBuffers(handler);
}

void Canvas::close()
{
	GLFWwindow* const handler = reinterpret_cast<GLFWwindow*>(m_handler);
	glfwSetWindowShouldClose(handler, true);
}

void Canvas::handleResize(GLFWwindow*, const int width, const int height)
{
	if (Canvas* const canvas = Canvas::instance())
	{
		canvas->m_width = width;
		canvas->m_height = height;
	}
}
