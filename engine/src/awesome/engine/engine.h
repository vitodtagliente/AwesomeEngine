#pragma once

#include <initializer_list>
#include <list>
#include <string>
#include <typeinfo>
#include <awesome/core/singleton.h>
#include <awesome/core/time.h>

namespace awesome
{
	class Module;

	class Engine final : public Singleton<Engine> 
	{
	public:

		// generic Engine Module interface

		class Module
		{
		public:

			enum class State
			{
				Unknown,
				Error,
				Started,
				Closed
			};

			// module initialization 
			bool startup();
			void shutdown();
			// update the module
			void update();
			// render phase
			void pre_rendering();
			void render();
			void post_rendering();

			// get the module state
			inline State getState() const { return m_state; }

		protected:

			// module specific implementation interface
			virtual bool startup_implementation() { return true; }
			virtual void shutdown_implementation() {}
			virtual void update_implementation() {}
			virtual void pre_rendering_implementation() {}
			virtual void render_implementation() {}
			virtual void post_rendering_implementation() {}

			// module state
			State m_state{ State::Unknown };

		};

		class Service
		{
		public:

			Service() = default;
			virtual ~Service() = default;

			virtual bool startup() = 0;
			virtual void shutdown() = 0;
		};

		Engine();
		~Engine();

		static void run(const std::initializer_list<Module*>& t_modules = {});

		template <class T>
		void registerModule(T* const t_module);

		template <class T>
		T* const getModule() const;

		template <class T>
		T* const getService() const;

	private:

		// launch the engine
		void launch(const std::initializer_list<Module*>& t_modules = {});

		// engine startup and shutdown
		bool startup(const std::initializer_list<Module*>& t_modules = {});
		void shutdown();
		// engine loop
		void update();
		void render();
		bool isRunning() const;

		// register the engine modules
		void registerModules();

		// engine time management
		Time m_time;
		// engine's modules
		std::list<std::pair<std::string, Module*>> m_modules;
		// engine's services
		std::list<Service*> m_services;
	};

	template <class T>
	void Engine::registerModule(T* const t_module)
	{
		static_assert(std::is_base_of<Module, T>(), "Invalid Module class");

		const std::type_info& ti = typeid(T);
		const std::string module_name{ ti.name() };

		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			if (it->first == module_name)
			{
				return;
			}
		}
		m_modules.push_back({ module_name, t_module });
	}

	template <class T>
	T* const Engine::getModule() const
	{
		static_assert(std::is_base_of<Module, T>(), "Invalid Module class");

		const std::type_info& ti = typeid(T);
		const std::string module_name{ ti.name() };

		for (auto it = m_modules.begin(); it != m_modules.end(); it++)
		{
			if (it->first == module_name)
			{
				return it->second;
			}
		}
		return nullptr;
	}

	template <class T>
	T* const Engine::getService() const
	{
		return nullptr;
	}
}