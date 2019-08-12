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
		virtual const std::map<std::string, std::string>& getDefaultShaderSources() const override;

	};
}