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
		delete m_api;
		delete m_input;
	}

	bool InputModule::startup_implementation()
	{
		// initialize the application API
		m_api = createAPI();
		assert(m_api != nullptr);
		if (m_api->startup())
		{
			m_input = new Input(m_api);
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