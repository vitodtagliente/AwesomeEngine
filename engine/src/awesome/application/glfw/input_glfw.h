#pragma once

#include "../input.h"

namespace awesome
{
	class InputGLFW final : public Input
	{
	public:

		virtual bool startup() override;
		virtual void shutdown() override;
	};
}