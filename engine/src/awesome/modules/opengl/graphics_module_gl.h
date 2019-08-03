#pragma once

#include <awesome/graphics/graphics_module.h>

namespace awesome
{
	class GraphicsModuleGL final : public GraphicsModule
	{
	public:

		GraphicsModuleGL();

	protected:

		virtual GraphicsAPI* const createAPI() const override;
		virtual Renderer* const createRenderer(GraphicsAPI* const t_api) const override;

	};
}