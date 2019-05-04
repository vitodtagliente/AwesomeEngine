#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Application : public Module<Application>
	{
	public:

		Application();
		virtual ~Application();

	protected:
		
		// module interface
		virtual bool startup_imp() override;

	};
}