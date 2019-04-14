#pragma once

namespace awesome
{
	// engine's core elements
	class Game;
	class Input;
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

		static Engine* getInstance();

		inline Game* getGame() const { return m_game; }
		inline Input* getInput() const { return m_input; }
		inline Window* getWindow() const { return m_window; }

	private:

		Engine(Game* t_game);
		~Engine();

		// launch the engine
		void launch();

		// singleton pattern
		static Engine* m_instance;
		// game logic
		Game* m_game;
		// engine input system
		Input* m_input;
		// engine time
		Time* m_time;
		// window
		Window* m_window;
	};
}