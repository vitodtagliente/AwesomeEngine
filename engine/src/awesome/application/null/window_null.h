#pragma once

#include "../window.h"

namespace awesome
{
	class WindowNULL final : public Window
	{
	public:

		virtual void setTitle(const std::string& t_title) override;
		virtual void resize(const uint32 t_width, const uint32 t_height) override;

	private:

		// open implementation
		virtual bool open(const Settings& t_settings) override;
		// close implementation
		virtual void close_implementation() override;

		// module update
		virtual void update_implementation() override;
	};
}