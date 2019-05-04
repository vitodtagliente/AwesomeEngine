#pragma once

#include <vector>
#include "../core/singleton.h"

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

		// engine's modules
		std::vector<class IModule*> m_modules;
	};
}