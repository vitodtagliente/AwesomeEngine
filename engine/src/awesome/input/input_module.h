#pragma once

#include <awesome/core/engine.h>

namespace awesome
{
	class InputAPI;

	class InputModule : public Engine::Module
	{
	public:

		InputModule();
		virtual ~InputModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		virtual InputAPI* const createAPI() const = 0;

		// api
		InputAPI* m_api;

	};
}