#pragma once

#include <map>
#include "../types.h"
#include "../math/vec2.h"

/*
The Input class manages the application input events.
It is responsible for storing keys and mouse buttons states.
*/

using namespace awesome::math;

namespace awesome
{
	// describes the key state
	enum KeyState : uint
	{
		Down = 0,
		Pressed = 1,
		Released = 2
	};

	// collection of keys
	struct KeyCode
	{
		static const uint Q;
		static const uint W;
		static const uint E;
		static const uint R;
		static const uint T;
		static const uint Y;
		static const uint U;
		static const uint I;
		static const uint O;
		static const uint P;
		static const uint A;
		static const uint S;
		static const uint D;
		static const uint F;
		static const uint G;
		static const uint H;
		static const uint J;
		static const uint K;
		static const uint L;
		static const uint Z;
		static const uint X;
		static const uint C;
		static const uint V;
		static const uint B;
		static const uint N;
		static const uint M;
		static const uint F1;
		static const uint F2;
		static const uint F3;
		static const uint F4;
		static const uint F5;
		static const uint F6;
		static const uint F7;
		static const uint F8;
		static const uint F9;
		static const uint F10;
		static const uint F11;
		static const uint F12;
		static const uint Enter;
		static const uint Space;
		static const uint Escape;
		static const uint UpArrow;
		static const uint DownArrow;
		static const uint RightArrow;
		static const uint LeftArrow;
		static const uint Keypad0;
		static const uint Keypad1;
		static const uint Keypad2;
		static const uint Keypad3;
		static const uint Keypad4;
		static const uint Keypad5;
		static const uint Keypad6;
		static const uint Keypad7;
		static const uint Keypad8;
		static const uint Keypad9;		
		static const uint LeftControl;
		static const uint RightControl;
		static const uint LeftAlt;
		static const uint RightAlt;
		static const uint LeftShift;
		static const uint RightShift;

		static const uint MouseButtonLeft;
		static const uint MouseButtonRight;
		static const uint MouseButtonWheel;
	};

	class InputManager final
	{
	private:

		friend class Window;
		
		InputManager() = default;
		~InputManager() = default;

		std::map<uint, KeyState> m_LastKeysState{};
		std::map<uint, KeyState> m_KeysState{};

		vec2 m_LastMousePosition{ 0.0f,0.0f };
		vec2 m_MousePosition{ 0.0f, 0.0f };
		vec2 m_MouseDeltaPosition{ 0.0f, 0.0f };
		
		bool m_IsMousePositionValid{ true };

		// events callbacks
		void onKeyCallback(const uint key_code, const KeyState key_state);
		void onMousePositionCallback(const float x, const float y);
		void onMouseEnterCallback(const bool entered);

		void init(void* const window_handler);
		void platformInit(void* const window_handler);

		void update();
		void platformUpdate();

		void clear();
		
	public:

		InputManager& operator=(InputManager&& input_manager) = delete;
		InputManager(const InputManager& input_manager) = delete;
		InputManager(InputManager&& input_manager) = delete;
		InputManager& operator= (const InputManager& input_manager) = delete;

		bool isKeyDown(const uint key_code) const;
		bool isKeyPressed(const uint key_code) const;
		bool isKeyReleased(const uint key_code) const;

		inline const vec2& getMousePosition() const { return m_MousePosition; }
		inline const vec2& getMouseDeltaPosition() const { return m_MouseDeltaPosition; }
		inline bool isMousePositionValid() const { return m_IsMousePositionValid; }
	};

	class Input
	{		
	private:

		static InputManager* m_MainInputManager;

		static InputManager* mainInputManager();

	public:
		
		inline static bool isKeyPressed(const uint key_code) {
			return mainInputManager()->isKeyPressed(key_code);
		}

		inline static bool isKeyReleased(const uint key_code) {
			return mainInputManager()->isKeyReleased(key_code);
		}

		inline static bool isKeyDown(const uint key_code) {
			return mainInputManager()->isKeyDown(key_code);
		}

		inline static const vec2& getMousePosition() {
			return mainInputManager()->getMousePosition();
		}

		inline static const vec2& getMouseDeltaPosition() {
			return mainInputManager()->getMouseDeltaPosition();
		}
	};
}