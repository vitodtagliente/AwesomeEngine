#pragma once

#include "../input.h"

namespace awesome
{
	class InputGLFW final : public Input
	{
	private:

		virtual void initialize(class Window* const t_window) override;
	};
}