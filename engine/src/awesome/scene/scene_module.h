#pragma once

#include "../engine/module.h"

namespace awesome
{
	class World;

	class SceneModule : public Module
	{
	public:

		SceneModule();
		~SceneModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;
		virtual void pre_rendering_implementation() override;
		virtual void render_implementation() override;
		virtual void post_rendering_implementation() override;

	private:

		// world instance
		World* m_world;
	};
}