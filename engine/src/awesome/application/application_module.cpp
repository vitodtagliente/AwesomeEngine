#include "application_module.h"

#include <cassert>

#include "application_api.h"
#include "application.h"

namespace awesome
{
	ApplicationModule::ApplicationModule()
		: m_api()
		, m_application()
	{
	}

	ApplicationModule::~ApplicationModule()
	{
		delete m_api;
		delete m_application;
	}

	bool ApplicationModule::startup_implementation()
	{
		// initialize the application API
		m_api = createAPI();
		assert(m_api != nullptr);
		// get the application context
		m_application = m_api->createApplication();
		assert(m_application != nullptr);
		// initialize the application
		return m_application->initialize();
	}

	void ApplicationModule::shutdown_implementation()
	{
		assert(m_application != nullptr);
		m_application->close();
	}

	void ApplicationModule::update_implementation()
	{
		m_application->update();
	}
}
