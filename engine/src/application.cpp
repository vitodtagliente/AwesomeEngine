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

	void Application::init()
	{
		for (auto it = modules.begin(); it != modules.end(); ++it) {
			if (*it != nullptr)
				(*it)->init();
			else modules.erase(it);
		}
	}

	void Application::update(float delta_time)
	{
		for (auto it = modules.begin(); it != modules.end(); ++it) {
			if (*it != nullptr)
				(*it)->update(delta_time);
			else modules.erase(it);
		}
	}

	void Application::render()
	{
		for (auto it = modules.begin(); it != modules.end(); ++it) {
			if (*it != nullptr)
				(*it)->render();
			else modules.erase(it);
		}
	}

	void Application::free()
	{
		for (auto it = modules.begin(); it != modules.end(); ++it) {
			if (*it != nullptr)
				(*it)->free();
			else modules.erase(it);
		}
	}
			
	void Application::run()
	{
		if (window != nullptr)
		{
			if (window->getStatus() == WindowStatus::Created)
			{
				configure();
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
				free();
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