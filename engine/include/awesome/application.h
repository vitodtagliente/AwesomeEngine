#pragma once

#include "windowing/window.h"
#include "rendering/renderer.h"

using namespace Awesome::Windowing;

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

		virtual void init() = 0;
		virtual void render() = 0;
		virtual void update(float deltaTime) = 0;

		void run();

	protected:
		ApplicationStatus status{ ApplicationStatus::Created };
		
		Application();
		~Application();

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

		ApplicationStatus getStatus() const { return status; }

		void close();
	};
}