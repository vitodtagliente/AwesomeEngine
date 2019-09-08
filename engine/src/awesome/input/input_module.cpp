#include "input_module.h"

#include <cassert>
#include "input.h"

namespace awesome
{
	InputModule::InputModule()
		: m_api()
		, m_input()
	{

	}

	InputModule::~InputModule()
	{

	}

	bool InputModule::startup_implementation()
	{
		// initialize the application API
		m_api = std::move(make_api());
		assert(m_api != nullptr);
		if (m_api->startup())
		{
			m_input = std::make_unique<Input>(*m_api);
			return true;
		}
		return false;
	}

	void InputModule::shutdown_implementation()
	{
		m_api->shutdown();
	}

	void InputModule::update_implementation()
	{
		m_input->update();
	}
}