#pragma once

#include "../graphics.h"

namespace awesome
{
	class GraphicsGL final : public Graphics
	{
	private:

		// module startup
		virtual bool startup_implementation() override;

		// module update
		virtual void update_implementation() override;
	};
}