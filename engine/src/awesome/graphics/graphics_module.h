#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Renderer;

	class GraphicsModule : public Module
	{
	public:

		enum class API
		{
			Null,
			OpenGL
		};

		GraphicsModule(const API t_api);
		~GraphicsModule();

		inline API getAPI() const { return m_api; }
		inline Renderer* getRenderer() const { return m_renderer; }

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		// used api
		API m_api;
		// renderer
		Renderer* m_renderer;
	};
}