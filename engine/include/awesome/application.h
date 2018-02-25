#pragma once

#include "windowing/window.h"
#include "rendering/render_pipeline.h"
#include "scenegraph/scene.h"

using namespace Awesome::Windowing;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;

namespace Awesome
{
	enum ApplicationStatus
	{
		Closing,
		Closed,
		Created,
		Pause,
		Running,
		Terminated
	};
	
	class Application
	{
	private:
		static Application* singleton;

		Window* window{ nullptr };

		void run();

		RenderPipeline* renderer{ nullptr };
		Scene* scene{ nullptr };

	protected:
		ApplicationStatus status{ ApplicationStatus::Created };
		
		Application();
		~Application();

		virtual void init() = 0;
		virtual void render() = 0;
		virtual void update(float deltaTime) = 0;

	public:

		template <class T>
		static void run()
		{
			if (singleton != nullptr)
				return;

			T* t_application = new T{};
			singleton = dynamic_cast<Application*>(t_application);
			if (singleton != nullptr)
				singleton->run();
		}

		static Application* instance() { return singleton; }

		Window* getWindow() const { return window; }
		RenderPipeline* getRenderer() const { return renderer; }
		Scene* getScene() const { return scene; }

		bool loadScene(std::string name);
		void switchPipeline(RenderPipeline* new_pipeline, bool free_current = false);
				
		ApplicationStatus getStatus() const { return status; }

		void close();
	};
}