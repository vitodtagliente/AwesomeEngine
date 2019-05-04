#include <awesome/core/input.h>
#include <awesome/core/engine.h>
#include <GLFW/glfw3.h>

namespace awesome
{
	void Input::platformInit(void * const t_windowHandler)
	{
		glfwSetKeyCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow*, const int t_key, const int, const int t_action, const int)
		{
			auto key_state = KeyState::Down;
			if (t_action == GLFW_PRESS)
				key_state = KeyState::Pressed;
			else if (t_action == GLFW_RELEASE)
				key_state = KeyState::Released;

			if (Input * input = Input::instance())
			{
				input->handleKeyCallback(t_key, key_state);
			}
		});

		glfwSetMouseButtonCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow*, const int t_button, const int t_action, int)
		{
			auto key_state = KeyState::Down;
			if (t_action == GLFW_PRESS)
				key_state = KeyState::Pressed;
			else if (t_action == GLFW_RELEASE)
				key_state = KeyState::Released;

			if (Input * input = Input::instance())
			{
				input->handleKeyCallback(t_button, key_state);
			}
		});

		glfwSetCursorPosCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow*, const double t_x, const double t_y)
		{
			if (Input * input = Input::instance())
			{
				input->handleMousePositionCallback(static_cast<float>(t_x), static_cast<float>(t_y));
			}
		});

		glfwSetCursorEnterCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow*, const int t_entered)
		{
			if (Input * input = Input::instance())
			{
				input->handleMouseEnterCallback(t_entered);
			}
		});
	}

	void Input::platformUpdate()
	{

	}

	void Input::platformUinit()
	{
	}
}