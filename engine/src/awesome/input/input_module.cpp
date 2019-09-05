#include "input_module.h"

#include <cassert>
#include "input_api.h"

namespace awesome
{
	InputModule::InputModule()
		: m_api()
	{

	}

	InputModule::~InputModule()
	{
		delete m_api;
	}

	bool InputModule::startup_implementation()
	{
		// initialize the application API
		m_api = createAPI();
		assert(m_api != nullptr);
		return true;
	}

	void InputModule::shutdown_implementation()
	{

	}

	void InputModule::update_implementation()
	{

	}

}