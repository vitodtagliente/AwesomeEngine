#include <awesome/application.h>
#include <glad/glad.h>

using namespace Awesome::Windowing;

namespace Awesome
{
	Application* Application::singleton = nullptr;
	
	Application::Application() {
		window = Window::open<Window>();
		status = ApplicationStatus::Running;
		scene = new Scene("default_scene");
		/* FIX later: Renderer could be changed at runtime */
		renderer = Renderer::instance();
		renderer->handleScene(scene);
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
				renderer->init();
				while (!window->shouldClose() && status != ApplicationStatus::Closing)
				{
					glClearColor(0.2f, 0.25f, 0.3f, 1.0f);

					auto delta_time = window->getTime();
					update(delta_time);
					if (renderer != nullptr)
					{
						renderer->update(delta_time);
						renderer->render();
					}
					render();

					window->update();
					glClear(GL_COLOR_BUFFER_BIT);
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