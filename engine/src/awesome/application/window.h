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

		Window();

		inline bool isOpen() const { return m_isOpen; }

		void close();

		virtual void setTitle(const std::string& t_title) = 0;
		virtual void resize(const uint32 t_width, const uint32 t_height) = 0;

	protected:

		// open the window 
		virtual bool open(const Settings& t_settings) = 0;
		virtual void close_implementation() = 0;

		// window state
		bool m_isOpen;

	private:

		// module startup
		virtual bool startup_implementation() override;
	};
}