#pragma once

#include <vector>
#include "windowing/window.h"
#include "rendering/render_pipeline.h"
#include "scene/scene.h"
#include "engine_module.h"

namespace Awesome
{
	enum class ApplicationStatus
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

		void init();
		void render();
		void update(float deltaTime);
		void free();

	protected:
		ApplicationStatus status{ ApplicationStatus::Created };
		
		Application();
		~Application();

		virtual void configure() {}
		virtual void onUpdate(float delta_time) {}

		std::vector<EngineModule*> modules;

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