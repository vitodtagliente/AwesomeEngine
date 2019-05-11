#pragma once

#include <map>
#include <string>
#include "../core/singleton.h"
#include "../core/types.h"

namespace awesome
{
	class Window : public Singleton<Window>
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

		Window();

		// open the window
		bool open(const Settings& t_settings);
		void close();
		// update the window
		void update();

		inline bool isOpen() const { return m_isOpen; }

		virtual void setTitle(const std::string& t_title) = 0;
		virtual void resize(const uint32 t_width, const uint32 t_height) = 0;

	protected:

		// open the window 
		virtual bool open_implementation(const Settings& t_settings) = 0;
		virtual void close_implementation() = 0;
		// update the window
		virtual void update_implementation() = 0;

		// window state
		bool m_isOpen;
	};
}