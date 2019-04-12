#pragma once

#include <functional>
#include <vector>

namespace awesome
{
	template <typename ReturnType, typename... Params>
	class BaseEvent
	{
	private:

		std::vector<std::function<ReturnType(Params...)>> m_listeners{};

	public:

		BaseEvent() = default;
		~BaseEvent() {
			m_listeners.clear();
		}

		inline void broadcast() 
		{
			for (auto listener : m_listeners) 
			{
				listener();
			}
		}

		inline void addListener(const std::function<ReturnType(Params...)>& function) {
			m_listeners.push_back(function);
		}

		inline bool removeListener(const std::function<ReturnType(Params...)>& function) {
			for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
			{
				if (*it == function)
				{
					m_listeners.erase(it);
					return true;
				}
			}
			return false;
		}

		inline void clear() {
			m_listeners.clear();
		}

	};

	typedef BaseEvent<void> Event;
}