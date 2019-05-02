#pragma once

#include <map>
#include <string>
#include "../core/types.h"
#include "../engine/module.h"

namespace awesome
{
	class Window : public Module<Window>
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

		virtual bool open(const Settings& t_settings) = 0;
		virtual void close();

		// check the window state
		State getState() const;

		virtual void setTitle(const std::string& t_title) = 0;
		virtual void resize(const uint32 t_width, const uint32 t_height) = 0;

	protected:

		// window state
		State m_state;
	};
}