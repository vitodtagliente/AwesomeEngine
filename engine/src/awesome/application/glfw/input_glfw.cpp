#include "input_glfw.h"

#include <GLFW/glfw3.h>
#include "window_glfw.h"

namespace awesome
{
	bool InputGLFW::startup()
	{
		if (WindowGLFW * window = dynamic_cast<WindowGLFW*>(Window::instance()))
		{
			glfwSetKeyCallback(
				window->getWindowHandler(),
				[](GLFWwindow*, const int t_key, const int, const int t_action, const int)
				{
					auto key_state = KeyState::Down;
					if (t_action == GLFW_PRESS)
						key_state = KeyState::Pressed;
					else if (t_action == GLFW_RELEASE)
						key_state = KeyState::Released;

					if (InputGLFW * const input = dynamic_cast<InputGLFW*>(Input::instance()))
					{
						input->handleKeyCallback(t_key, key_state);
					}
				});

			glfwSetMouseButtonCallback(
				window->getWindowHandler(),
				[](GLFWwindow*, const int t_button, const int t_action, int)
				{
					auto key_state = KeyState::Down;
					if (t_action == GLFW_PRESS)
						key_state = KeyState::Pressed;
					else if (t_action == GLFW_RELEASE)
						key_state = KeyState::Released;

					if (InputGLFW* const input = dynamic_cast<InputGLFW*>(Input::instance()))
					{
						input->handleKeyCallback(t_button, key_state);
					}
				});

			glfwSetCursorPosCallback(
				window->getWindowHandler(),
				[](GLFWwindow*, const double t_x, const double t_y)
				{
					if (InputGLFW * const input = dynamic_cast<InputGLFW*>(Input::instance()))
					{
						input->handleMousePositionCallback(static_cast<float>(t_x), static_cast<float>(t_y));
					}
				});

			glfwSetCursorEnterCallback(
				window->getWindowHandler(),
				[](GLFWwindow*, const int t_entered)
				{
					if (InputGLFW* const input = dynamic_cast<InputGLFW*>(Input::instance()))
					{
						input->handleMouseEnterCallback(t_entered);
					}
				});
			return true;
		}
		return false;
	}

	void InputGLFW::shutdown()
	{

	}
}