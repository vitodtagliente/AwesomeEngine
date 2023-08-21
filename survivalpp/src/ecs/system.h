/// Copyright (c) Vito Domenico Tagliente

#pragma once 

#include <cstddef>
#include <memory>
#include <tuple>
#include <vector>

#include "core/singleton.h"
#include "core/uuid.h"

#include "entity.h"
#include "component_array.h"

class ISystem
{
public:
	virtual ~ISystem() = default;
	virtual void run(double delta_time) = 0;

protected:
	virtual void pre_run(double delta_time) {}
};

class SystemRegistry final
{
public:
	struct Settings
	{
		bool multithreading{ true };
		std::size_t max_threads{ std::numeric_limits<std::size_t>::max() };
	};

	SystemRegistry(const Settings& settings = {});

	inline const std::vector<std::unique_ptr<ISystem>>& systems() const { return m_systems; }

	void run(double delta_time);

	void push_back(std::unique_ptr<ISystem> system);
	template <typename T, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
	void push_back()
	{
		m_systems.push_back(std::unique_ptr<ISystem>(new T()));
	}
	template <typename T, typename...A, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
	void push_back(A... args)
	{
		m_systems.push_back(std::unique_ptr<ISystem>(new T(args...)));
	}

private:
	Settings m_settings;
	std::vector<std::unique_ptr<ISystem>> m_systems;
};

template <typename T = Component, typename ...C>
class System : public ISystem
{
public:
	virtual void run(const double delta_time) final
	{
		pre_run(delta_time);

		if constexpr (sizeof...(C) == 0)
		{
			auto& data = ComponentArray<T>::instance().data();
			for (auto it = data.begin(); it != data.end(); ++it)
			{
				T& component = *it;
				if (component.enabled == false) continue;

				process(delta_time, component, ComponentArray<C>::instance().get(uuid::Invalid)...);
			}
		}
		else
		{
			std::size_t components_mask = ComponentArray<T>::instance().id();
			components_mask |= (ComponentArray<C>::instance().id() | ...);

			auto& entities = ComponentArray<T>::instance().entities();
			for (int i = 0; i < entities.size(); ++i)
			{
				const uuid& entity = entities[i];

				const std::size_t component_mask = EntityManager::components(entity);
				if ((component_mask & components_mask) != 0)
				{
					process(delta_time, ComponentArray<T>::instance().get(entity), ComponentArray<C>::instance().get(entity)...);
				}
			}
		}
	}

protected:
	virtual void process(double, T&, C&...) {};
};