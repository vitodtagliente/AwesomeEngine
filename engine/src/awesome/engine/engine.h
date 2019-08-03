#pragma once

#include <initializer_list>
#include <list>
#include <string>
#include <typeinfo>
#include <awesome/core/singleton.h>

namespace awesome
{
	class Module;

	class Engine final : public Singleton<Engine> 
	{
	public:

		Engine();
		~Engine();

		static void run(const std::initializer_list<Module*>& t_modules = {});

		template <class T>
		void registerModule(T* const t_module);

		template <class T>
		T* const getModule() const;

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

		// engine's modules
		std::list<std::pair<std::string, Module*>> m_modules;
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
}