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

	m_handler = glfwCreateWindow(
		settings.width,
		settings.height,
		settings.title.c_str(),
		false,
		false
	);

	if (m_handler == nullptr)
	{
		return false;
	}

	glfwMakeContextCurrent(m_handler);
	m_width = settings.width;
	m_height = settings.height;
	m_isOpen = true;

	// resize callback
	glfwSetFramebufferSizeCallback(m_handler, Canvas::handleResize);

	glfwSetKeyCallback(
		m_handler,
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
		m_handler,
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
		m_handler,
		[](GLFWwindow*, const double x, const double y)
		{
			if (Input* const input = Input::instance())
			{
				input->setMousePosition(static_cast<float>(x), static_cast<float>(y));
			}
		}
	);

	glfwSetCursorEnterCallback(
		m_handler,
		[](GLFWwindow*, const int entered)
		{
			if (Input* const input = Input::instance())
			{
				input->setMousePositionValid(entered);
			}
		}
	);

	return true;
}

void Canvas::update()
{
	glfwPollEvents();

	// check for closing window
	if (glfwWindowShouldClose(m_handler))
	{
		m_isOpen = false;
	}
	glfwSwapBuffers(m_handler);
}

void Canvas::close()
{
	glfwSetWindowShouldClose(m_handler, true);
}

void Canvas::handleResize(GLFWwindow*, const int width, const int height)
{
	if (Canvas* const canvas = Canvas::instance())
	{
		canvas->m_width = width;
		canvas->m_height = height;
	}
}
