#pragma once

#include "windowing/window.h"

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

		void run();

	protected:
		Application();
		~Application();

		virtual void init() = 0;
		virtual void render() = 0;
		virtual void update(float deltaTime) = 0;

		ApplicationStatus status{ ApplicationStatus::Created };
		
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