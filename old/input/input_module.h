#pragma once

#include <memory>
#include <awesome/core/api_wrapper.h>
#include <awesome/engine/engine.h>

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
		virtual std::unique_ptr<API> make_api() const = 0;

	private:

		// api
		std::unique_ptr<API> m_api;
		// input system
		std::unique_ptr<Input> m_input;

	};
}