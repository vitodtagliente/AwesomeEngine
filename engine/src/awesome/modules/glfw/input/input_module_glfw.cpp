#include "input_module_glfw.h"

#include <GLFW/glfw3.h>
#include "../window_glfw.h"
#include <awesome/input/keycode.h>
#include <awesome/input/input.h>

namespace awesome
{
	InputModuleGLFW::InputModuleGLFW()
	{
	}
	
	InputModuleGLFW::~InputModuleGLFW()
	{
	}
	
	InputModule::API* const InputModuleGLFW::createAPI() const
	{
		return new API_GLFW();
	}
	
	bool InputModuleGLFW::startup_implementation()
	{
		if (InputModule::startup_implementation())
		{
			bindWindowEvents();
			return true;
		}
		return false;
	}

	void InputModuleGLFW::shutdown_implementation()
	{
		unbindWindowEvents();
		InputModule::shutdown_implementation();
	}
	
	void InputModuleGLFW::bindWindowEvents()
	{
		if (WindowGLFW * window = static_cast<WindowGLFW*>(Window::instance()))
		{
			GLFWwindow* const window_handler = window->getWindowHandler();
			if (window_handler == nullptr)
			{
				return;
			}

			glfwSetKeyCallback(
				window_handler,
				[](GLFWwindow*, const int t_key, const int, const int t_action, const int)
				{
					auto key_state = KeyState::Down;
					if (t_action == GLFW_PRESS)
						key_state = KeyState::Pressed;
					else if (t_action == GLFW_RELEASE)
						key_state = KeyState::Released;

					if (Input * const input = Input::instance())
					{
						input->setKeyState(t_key, key_state);
					}
				}
			);

			glfwSetMouseButtonCallback(
				window_handler,
				[](GLFWwindow*, const int t_button, const int t_action, int)
				{
					auto key_state = KeyState::Down;
					if (t_action == GLFW_PRESS)
						key_state = KeyState::Pressed;
					else if (t_action == GLFW_RELEASE)
						key_state = KeyState::Released;

					if (Input * const input = Input::instance())
					{
						input->setKeyState(t_button, key_state);
					}
				}
			);

			glfwSetCursorPosCallback(
				window_handler,
				[](GLFWwindow*, const double t_x, const double t_y)
				{
					if (Input * const input = Input::instance())
					{
						input->setMousePosition(static_cast<float>(t_x), static_cast<float>(t_y));
					}
				}
			);

			glfwSetCursorEnterCallback(
				window_handler,
				[](GLFWwindow*, const int t_entered)
				{
					if (Input * const input = Input::instance())
					{
						input->setMousePositionValid(t_entered);
					}
				}
			);
		}
	}
	
	void InputModuleGLFW::unbindWindowEvents()
	{
	}
}