#include "application_module.h"

#include <cassert>
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

	}

	bool ApplicationModule::startup_implementation()
	{
		m_api = std::move(make_api());
		assert(m_api != nullptr);
		if (m_api->startup())
		{
			m_application = std::move(m_api->make_application());
			assert(m_application);
			// initialize the application
			return m_application->initialize();
		}
		return false;
	}

	void ApplicationModule::shutdown_implementation()
	{
		m_application->close();
	}

	void ApplicationModule::update_implementation()
	{
		m_application->update();
	}
}
