#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include <awesome/engine/module.h>

namespace awesome
{
	class GraphicsAPI;
	class Renderer;

	class GraphicsModule : public Module
	{
	public:

		GraphicsModule();
		~GraphicsModule();

		inline GraphicsAPI* getAPI() const { return m_api; }
		inline Renderer* getRenderer() const { return m_renderer; }

	protected:

		virtual GraphicsAPI* const createAPI() const = 0;
		virtual Renderer* const createRenderer(GraphicsAPI* const t_api) const = 0;

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;
		virtual void pre_rendering_implementation() override;
		virtual void render_implementation() override;
		virtual void post_rendering_implementation() override;

		virtual const std::map<std::string, std::string>& getDefaultShaderSources() const = 0;

		// used api
		GraphicsAPI* m_api;
		// renderer
		Renderer* m_renderer;

	private:

		void initializeDefaultMaterials();
	};
}