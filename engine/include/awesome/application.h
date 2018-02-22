#pragma once

#include "windowing/window.h"
#include "rendering/renderer.h"
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

		Renderer* renderer{ nullptr };
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
		Renderer* getRenderer() const { return renderer; }
		Scene* getScene() const { return scene; }
		
		ApplicationStatus getStatus() const { return status; }

		void close();
	};
}