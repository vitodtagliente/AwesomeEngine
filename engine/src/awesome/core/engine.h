#pragma once

namespace awesome
{
	// engine's core elements
	class Game;
	class Time;
	class Window;

	class Engine final
	{
	public:

		template <typename T>
		static void run()
		{
			static_assert(std::is_base_of<Game, T>(), "Invalid Game class type");
			Game* game = new T{};
			m_instance = new Engine(game);
			m_instance->launch();
			delete m_instance;
		}

	private:

		Engine(Game* t_game);
		~Engine();

		// launch the engine
		void launch();

		// singleton pattern
		static Engine* m_instance;
		// game logic
		Game* m_game;
		// engine time
		Time* m_time;
		// window
		Window* m_window;
	};
}