#pragma once

#include "engine.h"

namespace awesome
{
	class World;

	class SceneModule : public Engine::Module
	{
	public:

		SceneModule();
		~SceneModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

	private:

		// world instance
		World* m_world;
	};
}