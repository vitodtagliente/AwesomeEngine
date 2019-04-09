#include <awesome/platform.h>

#ifdef PLATFORM_DESKTOP

#include <awesome/core/input.h>
#include <awesome/core/application.h>
#include <GLFW/glfw3.h>

namespace awesome
{
	const uint KeyCode::Q = GLFW_KEY_Q;
	const uint KeyCode::W = GLFW_KEY_W;
	const uint KeyCode::E = GLFW_KEY_E;
	const uint KeyCode::R = GLFW_KEY_R;
	const uint KeyCode::T = GLFW_KEY_T;
	const uint KeyCode::Y = GLFW_KEY_Y;
	const uint KeyCode::U = GLFW_KEY_U;
	const uint KeyCode::I = GLFW_KEY_I;
	const uint KeyCode::O = GLFW_KEY_O;
	const uint KeyCode::P = GLFW_KEY_P;
	const uint KeyCode::A = GLFW_KEY_A;
	const uint KeyCode::S = GLFW_KEY_S;
	const uint KeyCode::D = GLFW_KEY_D;
	const uint KeyCode::F = GLFW_KEY_F;
	const uint KeyCode::G = GLFW_KEY_G;
	const uint KeyCode::H = GLFW_KEY_H;
	const uint KeyCode::J = GLFW_KEY_J;
	const uint KeyCode::K = GLFW_KEY_K;
	const uint KeyCode::L = GLFW_KEY_L;
	const uint KeyCode::Z = GLFW_KEY_Z;
	const uint KeyCode::X = GLFW_KEY_X;
	const uint KeyCode::C = GLFW_KEY_C;
	const uint KeyCode::V = GLFW_KEY_V;
	const uint KeyCode::B = GLFW_KEY_B;
	const uint KeyCode::N = GLFW_KEY_N;
	const uint KeyCode::M = GLFW_KEY_M;
	const uint KeyCode::F1 = GLFW_KEY_F1;
	const uint KeyCode::F2 = GLFW_KEY_F2;
	const uint KeyCode::F3 = GLFW_KEY_F3;
	const uint KeyCode::F4 = GLFW_KEY_F4;
	const uint KeyCode::F5 = GLFW_KEY_F5;
	const uint KeyCode::F6 = GLFW_KEY_F6;
	const uint KeyCode::F7 = GLFW_KEY_F7;
	const uint KeyCode::F8 = GLFW_KEY_F8;
	const uint KeyCode::F9 = GLFW_KEY_F9;
	const uint KeyCode::F10 = GLFW_KEY_F10;
	const uint KeyCode::F11 = GLFW_KEY_F11;
	const uint KeyCode::F12 = GLFW_KEY_F12;
	const uint KeyCode::Enter = GLFW_KEY_ENTER;
	const uint KeyCode::Space = GLFW_KEY_SPACE;
	const uint KeyCode::Escape = GLFW_KEY_ESCAPE;
	const uint KeyCode::UpArrow = GLFW_KEY_UP;
	const uint KeyCode::DownArrow = GLFW_KEY_DOWN;
	const uint KeyCode::RightArrow = GLFW_KEY_RIGHT;
	const uint KeyCode::LeftArrow = GLFW_KEY_LEFT;
	const uint KeyCode::Keypad0 = GLFW_KEY_0;
	const uint KeyCode::Keypad1 = GLFW_KEY_1;
	const uint KeyCode::Keypad2 = GLFW_KEY_2;
	const uint KeyCode::Keypad3 = GLFW_KEY_3;
	const uint KeyCode::Keypad4 = GLFW_KEY_4;
	const uint KeyCode::Keypad5 = GLFW_KEY_5;
	const uint KeyCode::Keypad6 = GLFW_KEY_6;
	const uint KeyCode::Keypad7 = GLFW_KEY_7;
	const uint KeyCode::Keypad8 = GLFW_KEY_8;
	const uint KeyCode::Keypad9 = GLFW_KEY_9;
	const uint KeyCode::LeftControl = GLFW_KEY_LEFT_CONTROL;
	const uint KeyCode::RightControl = GLFW_KEY_RIGHT_CONTROL;
	const uint KeyCode::LeftAlt = GLFW_KEY_LEFT_ALT;
	const uint KeyCode::RightAlt = GLFW_KEY_RIGHT_ALT;
	const uint KeyCode::LeftShift = GLFW_KEY_LEFT_SHIFT;
	const uint KeyCode::RightShift = GLFW_KEY_RIGHT_SHIFT;

	const uint KeyCode::MouseButtonLeft = GLFW_MOUSE_BUTTON_1;
	const uint KeyCode::MouseButtonRight = GLFW_MOUSE_BUTTON_2;
	const uint KeyCode::MouseButtonWheel = GLFW_MOUSE_BUTTON_3;

	void InputManager::platformInit(void* const window_handler) {
		glfwSetKeyCallback(
			static_cast<GLFWwindow*>(window_handler),
			[](GLFWwindow* window_handler, const int key, int /*scan_code*/, const int action, int /*mods*/)
		{
			auto key_state = KeyState::Down;
			if (action == GLFW_PRESS)
				key_state = KeyState::Pressed;
			else if (action == GLFW_RELEASE)
				key_state = KeyState::Released;

			auto window = Window::instance(window_handler);
			if (window)
				window->m_InputManager->onKeyCallback(key, key_state);
		});

		glfwSetMouseButtonCallback(
			static_cast<GLFWwindow*>(window_handler),
			[](GLFWwindow* window_handler, const int button, const int action, int /*mods*/)
		{
			auto key_state = KeyState::Down;
			if (action == GLFW_PRESS)
				key_state = KeyState::Pressed;
			else if (action == GLFW_RELEASE)
				key_state = KeyState::Released;

			auto window = Window::instance(window_handler);
			if (window)
				window->m_InputManager->onKeyCallback(button, key_state);
		});

		glfwSetCursorPosCallback(
			static_cast<GLFWwindow*>(window_handler),
			[](GLFWwindow* window_handler, const double x, const double y)
		{
			auto window = Window::instance(window_handler);
			if (window)
				window->m_InputManager->onMousePositionCallback(static_cast<float>(x), static_cast<float>(y));
		});

		glfwSetCursorEnterCallback(
			static_cast<GLFWwindow*>(window_handler),
			[](GLFWwindow* window_handler, const int entered)
		{
			auto window = Window::instance(window_handler);
			if (window)
				window->m_InputManager->onMouseEnterCallback(entered);
		});		
	}

	void InputManager::platformUpdate() {
		
	}
}

#endif 