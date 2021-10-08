#include "canvas.h"

#include "keycode.h"
#include "input.h"

Canvas::Canvas()
	: m_isOpen(false)
	, m_handler()
{
}

bool Canvas::init()
{
	if (glfwInit())
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// return gladLoadGL();
		return true;
	}
	return false;
}

bool Canvas::open(Settings settings)
{
	m_handler = glfwCreateWindow(
		settings.width,
		settings.height,
		settings.title.c_str(),
		false,
		false
	);

	if (m_handler != nullptr)
	{
		glfwMakeContextCurrent(m_handler);

		// resize callback
		glfwSetFramebufferSizeCallback(
			m_handler,
			[](GLFWwindow*, int width, int height)
			{

			}
		);

		glfwSetKeyCallback(
			m_handler,
			[](GLFWwindow*, const int key, const int, const int action, const int)
			{
				auto key_state = KeyState::Down;
				if (action == GLFW_PRESS)
					key_state = KeyState::Pressed;
				else if (action == GLFW_RELEASE)
					key_state = KeyState::Released;

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
					key_state = KeyState::Pressed;
				else if (action == GLFW_RELEASE)
					key_state = KeyState::Released;

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

		m_isOpen = true;
		return true;
	}
	return false;
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
}

int Canvas::width() const
{
	int width, height;
	glfwGetWindowSize(m_handler, &width, &height);
	return width;
}

int Canvas::height() const
{
	int width, height;
	glfwGetWindowSize(m_handler, &width, &height);
	return height;
}
