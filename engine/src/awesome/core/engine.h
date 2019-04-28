#pragma once

#include <cassert>
#include <map>
#include <string>
#include <typeinfo>
#include "singleton.h"

namespace awesome
{
	// engine's core elements
	class Game;
	class Input;
	class Renderer;
	class Time;
	class Window;

	class ISubsystem;

	class Engine final : public Singleton<Engine>
	{
	public:

		template <typename T>
		static void run()
		{
			static_assert(std::is_base_of<Game, T>(), "Invalid Game class type");
			Game* game = new T();
			m_instance = new Engine(game);
			m_instance->launch();
			delete m_instance;
		}

		template <typename T>
		void registerSubsystem(T* t_module)
		{
			static_assert(std::is_base_of<ISubsystem, T>(), "Invalid subsystem type");

			const std::type_info& typeinfo = typeid(T);
			m_subsystems.insert({
				{ typeinfo.name() }, 
				t_module
			});
		}

		template <typename T>
		T* getSubsystem() const
		{
			static_assert(std::is_base_of<ISubsystem, T>(), "Invalid subsystem type");

			const std::type_info& typeinfo = typeid(T);
			auto it = m_subsystems.find({ typeinfo.name() });
			if (it != m_subsystems.end())
			{
				return static_cast<T*>(it->second);
			}
			return nullptr;
		}

	private:

		Engine(Game* t_game);
		~Engine();

		// launch the engine
		void launch();

		// game logic
		Game* m_game;
		// engine input system
		Input* m_input;
		// renderer
		Renderer* m_renderer;
		// engine time
		Time* m_time;
		// window
		Window* m_window;

		// engine modules
		std::map<std::string, ISubsystem*> m_subsystems;
	};
}