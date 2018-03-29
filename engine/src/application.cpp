#include <awesome/application.h>
#include <awesome/rendering/objects/camera.h>

namespace Awesome
{
	Application* Application::singleton = nullptr;
	
	Application::Application() {
		window = Window::open<Window>();
		status = ApplicationStatus::Running;
		loadScene("default_scene");
		/* FIX later: Renderer could be changed at runtime */
		renderer = new RenderPipeline(scene);
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
					Camera::clear();

					auto delta_time = window->getTime();
					update(delta_time);
					if (renderer != nullptr)
					{
						renderer->update(delta_time);
						renderer->render();
					}
					render();

					window->update();
				}
				status = ApplicationStatus::Closed;
				window->close();
			}
		}
	}

	bool Application::loadScene(std::string name)
	{
		if (scene != nullptr)
		{
			scene->unload();
			delete scene;
		}
		/* TODO: check for file name */
		scene = new Scene();
		return true;
	}

	void Application::switchPipeline(RenderPipeline* new_pipeline, bool free_current/* = false*/)
	{
		if (free_current) {
			delete renderer;
		}
		renderer = new_pipeline;
		renderer->renderScene(scene);
	}

	void Application::close()
	{

	}
}