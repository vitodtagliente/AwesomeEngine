#pragma once

#include "../application.h"

namespace awesome
{
	class ApplicationNULL: public Application
	{
	public:

		virtual void registerModules() override;

	private:

		// module startup
		virtual void update_implementation() override;

	};
}