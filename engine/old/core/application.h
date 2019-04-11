#pragma once

#include <cassert>
#include <vector>
#include "window.h"
#include "application_behaviour.h"

namespace awesome
{
	// application states
	enum class ApplicationState
	{
		Closing,
		Closed,
		Created,
		Pause,
		Running,
		Terminated
	};

	class Application final
	{
	private:

		// singleton pattern
		static Application* m_Instance;

		// launch the application
		void launch();

		// application main window
		Window* m_Window{ nullptr };

		// application state
		ApplicationState m_State{ ApplicationState::Created };

		// application behaviours
		std::vector<ApplicationBehaviour*> m_Behaviours{};

		Application(const std::string& name, const WindowProperties& properties);
		~Application();

		// fps info
		uint8 m_FPS{ 1 };
		uint8 m_LastFPS{ 0 };

		// update time
		float m_UpdateTime{ 0.0f };

		void update();
		void updateFPS();
		void render();

	public:

		Application& operator=(Application&& application) = delete;
		Application(const Application& application) = delete;
		Application(Application&& application) = delete;
		Application& operator= (const Application& application) = delete;

		// singleton pattern
		static void run(
			const std::string& name, 
			const WindowProperties& properties,
			const std::vector<ApplicationBehaviour*>& behaviours = {}
		) {
			if (m_Instance != nullptr)
				return;
			m_Instance = new Application(name, properties);
			m_Instance->m_Behaviours = behaviours;
			m_Instance->launch();
		}

		// get the application instance
		static inline Application* instance() { return m_Instance; }
		// delete the application instance
		static inline void free() { delete m_Instance; }

		inline ApplicationState getState() const { return m_State; }

		// pause/resume 
		void pause();
		void resume();

		// get the main window
		inline Window* getWindow() const { return m_Window; }

		inline float getRenderTime() const { return m_Window->getTimePerFrame(); }
		inline float getUpdateTime() const { return m_UpdateTime; }
		inline uint8 getRealFPS() const { return m_LastFPS; }

		void close();
	};
}