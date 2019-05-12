#pragma once

#include "../graphics_module.h"

namespace awesome
{
	class GraphicsModuleGL final : public GraphicsModule
	{
	public:

		GraphicsModuleGL();
		~GraphicsModuleGL();

	protected:

		virtual bool startup_implementation() override;

	};
}