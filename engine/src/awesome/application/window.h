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

		virtual bool open(const Settings& t_settings) = 0;
		virtual void close() = 0;

		virtual void setTitle(const std::string& t_title) = 0;
		virtual void resize(const uint32 t_width, const uint32 t_height) = 0;

	private:

		// module startup
		virtual bool startup_imp() override;
	};
}