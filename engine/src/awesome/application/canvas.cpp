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
				// if (WindowGLFW* const window = static_cast<WindowGLFW*>(Window::instance()))
				// {
				// 	window->m_size = {
				// 		static_cast<uint32>(t_width),
				// 		static_cast<uint32>(t_height)
				// 	};
				// }
				// // #todo
				// if (Renderer* const renderer = Renderer::instance())
				// {
				// 	renderer->setViewport(t_width, t_height);
				// }
			}
		);

		glfwSetKeyCallback(
			m_handler,
			[](GLFWwindow*, const int t_key, const int, const int t_action, const int)
			{
				auto key_state = KeyState::Down;
				if (t_action == GLFW_PRESS)
					key_state = KeyState::Pressed;
				else if (t_action == GLFW_RELEASE)
					key_state = KeyState::Released;

				if (Input* const input = Input::instance())
				{
					input->setKeyState(t_key, key_state);
				}
			}
		);

		glfwSetMouseButtonCallback(
			m_handler,
			[](GLFWwindow*, const int t_button, const int t_action, int)
			{
				auto key_state = KeyState::Down;
				if (t_action == GLFW_PRESS)
					key_state = KeyState::Pressed;
				else if (t_action == GLFW_RELEASE)
					key_state = KeyState::Released;

				if (Input* const input = Input::instance())
				{
					input->setKeyState(t_button, key_state);
				}
			}
		);

		glfwSetCursorPosCallback(
			m_handler,
			[](GLFWwindow*, const double t_x, const double t_y)
			{
				if (Input* const input = Input::instance())
				{
					input->setMousePosition(static_cast<float>(t_x), static_cast<float>(t_y));
				}
			}
		);

		glfwSetCursorEnterCallback(
			m_handler,
			[](GLFWwindow*, const int t_entered)
			{
				if (Input* const input = Input::instance())
				{
					input->setMousePositionValid(t_entered);
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
