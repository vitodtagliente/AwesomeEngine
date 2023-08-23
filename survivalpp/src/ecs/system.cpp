#include "system.h"

#include <algorithm>
#include <execution>

void SystemRegistry::push_back(std::unique_ptr<ISystem> system)
{
	m_systems.push_back(std::move(system));
}

SystemRegistry::SystemRegistry(const Settings& settings) 
	: m_settings(settings)
{

}

void SystemRegistry::run(const double delta_time)
{
	if (m_settings.multithreading)
	{
		std::for_each(
			std::execution::seq,
			m_systems.begin(),
			m_systems.end(),
			[delta_time](const std::unique_ptr<ISystem>& system) -> void { system->run(delta_time); }
		);
	}
	else
	{
		for (const auto& system : m_systems)
		{
			system->run(delta_time);
		}
	}
}