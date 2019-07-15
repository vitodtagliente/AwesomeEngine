#pragma once

#include "../core/singleton.h"

namespace awesome
{
	class ApplicationAPI;

	class Application : public Singleton<Application>
	{
	public:
		
		Application();

		void initialize();
		
		void update();
	};
}