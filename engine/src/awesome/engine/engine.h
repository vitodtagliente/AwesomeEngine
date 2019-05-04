#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>
#include "../core/singleton.h"

namespace awesome
{
	class IModule;
	class Application;

	class Engine final : public Singleton<Engine> 
	{
	public:

		Engine();
		~Engine();

		static void run(const std::initializer_list<IModule*>& t_modules = {});

		template <class T>
		void registerModule(T* const t_module);

		template <class T>
		T* const getModule() const;

	private:

		// launch the engine
		void launch(const std::initializer_list<IModule*>& t_modules = {});

		// engine startup and shutdown
		bool startup(const std::initializer_list<IModule*>& t_modules = {});
		void shutdown();
		// engine loop
		void update();
		bool isRunning() const;

		// register the engine modules
		void registerModules();

		// application instance
		Application* m_application;
		// engine's modules
		std::map<std::string, IModule*> m_modules;
	};

	template <class T>
	void Engine::registerModule(T* const t_module)
	{
		static_assert(std::is_base_of<IModule, T>(), "Invalid Module class");

		const std::type_info& ti = typeid(T);
		const std::string module_name{ ti.name() };

		auto find = m_modules.find(module_name);
		if (find == m_modules.end())
		{
			m_modules.insert({ module_name, t_module });
		}
	}

	template <class T>
	T* const Engine::getModule() const
	{
		static_assert(std::is_base_of<IModule, T>(), "Invalid Module class");

		const std::type_info& ti = typeid(T);
		const std::string module_name{ ti.name() };

		auto find = m_modules.find(module_name);
		if (find == m_modules.end())
		{
			return find->second;
		}
		return nullptr;
	}
}