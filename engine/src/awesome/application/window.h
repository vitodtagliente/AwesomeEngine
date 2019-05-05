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

		enum class State
		{
			Unknown,
			Open,
			Closing,
			Closed,
			Error,
			PendingClose
		};

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

		inline State getState() const { return m_state; }
		inline bool isOpen() const
		{
			return m_state == State::Open || m_state == State::PendingClose || m_state == State::Closing;
		}
		inline bool shouldClose() const { return m_state == State::PendingClose; }

		bool close();

		virtual void setTitle(const std::string& t_title) = 0;
		virtual void resize(const uint32 t_width, const uint32 t_height) = 0;

	protected:

		// open the window 
		virtual bool open(const Settings& t_settings) = 0;
		virtual bool close_implementation() = 0;

		// window state
		State m_state;

	private:

		// module startup
		virtual bool startup_implementation() override;
	};
}