#pragma once

#include <map>
#include <string>
#include "../types.h"
#include "input.h"

namespace awesome
{
	// window's properties structure
	struct WindowProperties
	{
		uint32 width{ 640 };
		uint32 height{ 480 };
		bool fullscreen{ false };
		bool vSync{ false };
		uint8 fps{ 60 };
	};

	// window states
	enum WindowState
	{
		Created,
		Open,
		Closing,
		Closed,
		Error
	};

	class Window final
	{
	private:

		// Each window has one input manager
		// and the window is responsible for it's 
		// input manager updates
		friend class InputManager;

		// window's title
		std::string m_Title;
		// window's properties (width, height, ...)
		WindowProperties m_Properties;
		// window's state
		WindowState m_State{ WindowState::Created };
		// has the window the focus?
		bool m_HasFocus{ true };

		// platform specific implementations
		void platformClear();
		bool platformOpen();
		void platformUpdate();

		// window handler, platform specific type
		void* m_WindowHandler{ nullptr };
		// input manager
		InputManager* m_InputManager{ nullptr };

		// store all windows
		static std::map<void* const, Window* const> m_Windows;

		// time per frames
		float m_TimePerFrame{ 0.0f };

	public:

		Window(const std::string& title, const WindowProperties& properties);
		~Window();

		Window& operator=(Window&& window) = delete;
		Window(const Window& window) = delete;
		Window(Window&& window) = delete;
		Window& operator= (const Window& window) = delete;
		
		// getters and setters 
		inline uint32 getWidth() const { return m_Properties.width; }
		inline uint32 getHeight() const { return m_Properties.height; }

		void resize(const uint32 width, const uint32 height);

		inline bool isVSyncEnabled() const { return m_Properties.vSync; }
		void enableVSync(const bool enabled);

		inline uint8 getFPS() const { return m_Properties.fps; }
		void setFPS(const uint8 fps);
		inline float getTimePerFrame() const { return m_TimePerFrame; }

		inline bool hasFocus() const { return m_HasFocus; }

		inline bool isFullscreen() const { return m_Properties.fullscreen; }

		inline WindowState getState() const { return m_State; }
		inline bool isClosed() const { return m_State == WindowState::Closed; }

		void setTitle(const std::string& title);

		inline const void* getHandler() const { return m_WindowHandler; }
		inline InputManager* getInputManager() const { return m_InputManager; }

		void clear();
		void open();
		void update();
		void close();

		// find a window by handler
		static Window* instance(void* const window_handler);
	};
}