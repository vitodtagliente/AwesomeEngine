#pragma once

#include <map>
#include <string>
#include "singleton.h"
#include "../types.h"

namespace awesome
{
	class Window final : public Singleton<Window>
	{
	public:

		friend class Engine;

		// generic window settings
		struct Settings
		{
			std::string title;
			uint32 width, height;
			bool fullscreen;
			bool vsync;

			Settings();
		};

		// window state
		enum class State
		{
			Unknown,
			Created,
			Open,
			Closing,
			Closed,
			Error
		};

		Window& operator=(Window&& t_window) = delete;
		Window(const Window& t_window) = delete;
		Window(Window&& t_window) = delete;
		Window& operator= (const Window& t_window) = delete;

		// check the window state
		inline State getState() const { return m_state; }
		inline void* getWindowHandler() const { return m_windowHandler; }
		
		void setTitle(const std::string& t_title);
		void resize(const uint32 t_width, const uint32 t_height);
		
	private:
		
		Window();
		~Window();

		bool open(const Settings& t_settings);
		bool platformOpen(const Settings& t_settings);
		void update();
		void platformUpdate();
		void close();

		// window state
		State m_state;
		// window handler, platform specific type
		void* m_windowHandler;
	};
}