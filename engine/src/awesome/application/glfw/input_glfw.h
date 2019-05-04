#pragma once

#include "../input.h"

namespace awesome
{
	class InputGLFW final : public Input
	{
	private:

		virtual bool startup_imp() override;
		virtual void shutdown_imp() override;
	};
}