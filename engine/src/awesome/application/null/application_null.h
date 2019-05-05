#pragma once

#include "../application.h"

namespace awesome
{
	class ApplicationNULL: public Application
	{
	private:

		// module startup
		virtual void registerModules(class Engine* const t_engine);

	};
}