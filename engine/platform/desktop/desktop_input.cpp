#include <awesome/core/input.h>
#include <awesome/core/engine.h>
#include <GLFW/glfw3.h>

namespace awesome
{
	void Input::platformInit(void * const t_windowHandler)
	{
		glfwSetKeyCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow* t_windowHandler, const int t_key, const int /*t_scan_code*/, 
				const int t_action, const int /*t_mods*/)
		{
			auto key_state = KeyState::Down;
			if (t_action == GLFW_PRESS)
				key_state = KeyState::Pressed;
			else if (t_action == GLFW_RELEASE)
				key_state = KeyState::Released;

			Engine::getInstance()->getInput()->handleKeyCallback(t_key, key_state);
		});

		glfwSetMouseButtonCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow* t_windowHandler, const int t_button, const int t_action, int /*t_mods*/)
		{
			auto key_state = KeyState::Down;
			if (t_action == GLFW_PRESS)
				key_state = KeyState::Pressed;
			else if (t_action == GLFW_RELEASE)
				key_state = KeyState::Released;

			Engine::getInstance()->getInput()->handleKeyCallback(t_button, key_state);
		});

		glfwSetCursorPosCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow* t_windowHandler, const double t_x, const double t_y)
		{
			Engine::getInstance()->getInput()->handleMousePositionCallback(t_x, t_y);
		});

		glfwSetCursorEnterCallback(
			static_cast<GLFWwindow*>(t_windowHandler),
			[](GLFWwindow* t_windowHandler, const int t_entered)
		{
			Engine::getInstance()->getInput()->handleMouseEnterCallback(t_entered);
		});
	}

	void Input::platformUpdate()
	{

	}

	void Input::platformUinit()
	{
	}
}