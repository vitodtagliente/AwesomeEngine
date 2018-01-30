#include <dreamkeeper/application.h>

namespace Dreamkeeper
{
	Application::Application() {
		singleton = this;
		running = true;
	}

	Application::~Application() {

	}

	Application* Application::singleton = nullptr;

	Application* Application::instance() {
		return singleton;
	}
	
	void Application::close()
	{
		running = false;
	}

	bool Application::isRunning() const
	{
		return running;
	}
}