#pragma once

#include "../input.h"

namespace awesome
{
	class InputGLFW final : public Input
	{
	private:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
	};
}