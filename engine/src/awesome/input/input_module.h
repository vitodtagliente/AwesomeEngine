#pragma once

#include <awesome/core/api_wrapper.h>
#include <awesome/core/engine.h>

namespace awesome
{
	class Input;

	class InputModule : public Engine::Module
	{
	public:
		
		// Input API abstraction
		class API : public APIWrapper
		{
		public:
			API() = default; 
			virtual ~API() = default;
		};

		InputModule();
		virtual ~InputModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;

		// create the appropriate api
		virtual API* const createAPI() const = 0;

	private:

		// api
		API* m_api;
		// input system
		Input* m_input;

	};
}