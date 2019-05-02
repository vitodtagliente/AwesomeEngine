#pragma once

#include "../core/types.h"

namespace awesome
{
	// define a keycode type alias
	using keycode_t = uint32;

	// describes the key state
	enum class KeyState
	{
		Down,
		Pressed,
		Released
	};

	// collection of keys
	struct KeyCode
	{
		KeyCode() = delete;
		~KeyCode() = delete;

		static const keycode_t Q;
		static const keycode_t W;
		static const keycode_t E;
		static const keycode_t R;
		static const keycode_t T;
		static const keycode_t Y;
		static const keycode_t U;
		static const keycode_t I;
		static const keycode_t O;
		static const keycode_t P;
		static const keycode_t A;
		static const keycode_t S;
		static const keycode_t D;
		static const keycode_t F;
		static const keycode_t G;
		static const keycode_t H;
		static const keycode_t J;
		static const keycode_t K;
		static const keycode_t L;
		static const keycode_t Z;
		static const keycode_t X;
		static const keycode_t C;
		static const keycode_t V;
		static const keycode_t B;
		static const keycode_t N;
		static const keycode_t M;
		static const keycode_t F1;
		static const keycode_t F2;
		static const keycode_t F3;
		static const keycode_t F4;
		static const keycode_t F5;
		static const keycode_t F6;
		static const keycode_t F7;
		static const keycode_t F8;
		static const keycode_t F9;
		static const keycode_t F10;
		static const keycode_t F11;
		static const keycode_t F12;
		static const keycode_t Enter;
		static const keycode_t Space;
		static const keycode_t Escape;
		static const keycode_t UpArrow;
		static const keycode_t DownArrow;
		static const keycode_t RightArrow;
		static const keycode_t LeftArrow;
		static const keycode_t Keypad0;
		static const keycode_t Keypad1;
		static const keycode_t Keypad2;
		static const keycode_t Keypad3;
		static const keycode_t Keypad4;
		static const keycode_t Keypad5;
		static const keycode_t Keypad6;
		static const keycode_t Keypad7;
		static const keycode_t Keypad8;
		static const keycode_t Keypad9;
		static const keycode_t LeftControl;
		static const keycode_t RightControl;
		static const keycode_t LeftAlt;
		static const keycode_t RightAlt;
		static const keycode_t LeftShift;
		static const keycode_t RightShift;

		static const keycode_t MouseLeftButton;
		static const keycode_t MouseRightButton;
		static const keycode_t MouseWheelButton;
	};
}