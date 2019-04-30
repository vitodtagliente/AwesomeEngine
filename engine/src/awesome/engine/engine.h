#pragma once

#include "singleton.h"

namespace awesome
{
	class Engine final : Singleton<Engine> 
	{
	public:

		Engine();
		~Engine();

	private:

		void gameloop();

		// application instance
		class Application* m_application;

		// module manager instance
		class ModuleManager* m_moduleManager;

	};
}