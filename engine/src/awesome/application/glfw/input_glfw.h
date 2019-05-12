#pragma once

#include "../input.h"

namespace awesome
{
	class InputGLFW final : public Input
	{
	private:

		virtual bool initialize(class Window* const t_window) override;
		virtual void update_implementation() override;
	};
}