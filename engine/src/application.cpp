#include <awesome/application.h>
#include <glad/glad.h>

using namespace Awesome::Windowing;

namespace Awesome
{
	Application* Application::singleton = nullptr;
	
	Application::Application() {
		window = Window::open<Window>();
		status = ApplicationStatus::Running;
	}

	Application::~Application() {

	}
		
	void Application::run()
	{
		if (window != nullptr)
		{
			if (window->getStatus() == WindowStatus::Created)
			{
				init();
				while (!window->shouldClose() && status != ApplicationStatus::Closing)
				{
					glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT);

					update(window->getTime());
					render();

					window->update();
				}
				status = ApplicationStatus::Closed;
				window->close();
			}
		}
	}

	void Application::close()
	{

	}
}