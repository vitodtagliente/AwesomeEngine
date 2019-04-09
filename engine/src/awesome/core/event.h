#pragma once

#include <functional>
#include <vector>

namespace awesome
{
	template <typename ReturnType, typename... Params>
	class BaseEvent
	{
	private:

		std::vector<std::function<ReturnType(Params...)>> m_Listeners{};

	public:

		BaseEvent() = default;
		~BaseEvent() {
			m_Listeners.clear();
		}

		inline void broadcast() {
			for (auto listener : m_Listeners) {
				listener();
			}
		}

		inline void addListener(const std::function<ReturnType(Params...)>& function) {
			m_Listeners.push_back(function);
		}

		inline bool removeListener(const std::function<ReturnType(Params...)>& function) {
			for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
			{
				if (*it == function)
				{
					m_Listeners.erase(it);
					return true;
				}
			}
			return false;
		}

		inline void clear() {
			m_Listeners.clear();
		}

	};

	typedef BaseEvent<void> Event;
}