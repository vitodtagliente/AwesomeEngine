#pragma once

#include <map>
#include <string>
#include "../types.h"

namespace awesome
{
	class Window
	{
	public:

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

		Window();
		virtual ~Window();

		Window& operator=(Window&& t_window) = delete;
		Window(const Window& t_window) = delete;
		Window(Window&& t_window) = delete;
		Window& operator= (const Window& t_window) = delete;

		// check the window state
		inline State getState() const { return m_state; }

		bool open(const Settings& t_settings);
		void update();
		void close();

		void setTitle(const std::string& t_title);
		void resize(const uint32 t_width, const uint32 t_height);

	protected:

		virtual bool platformOpen(const Settings& t_settings);
		virtual void platformUpdate();

	private:

		// window state
		State m_state;
		// window handler, platform specific type
		void* m_windowHandler;

	};
}