#pragma once

#include <functional>
#include <vector>

namespace awesome
{
	template <typename ReturnType, typename... Params>
	class event_t
	{
	public:

		event_t()
			: m_listeners()
		{

		}

		~event_t() = default;

		inline void broadcast(Params... t_args) 
		{
			for (const auto& listener : m_listeners) 
			{
				listener(t_args...);
			}
		}

		inline void addListener(const std::function<ReturnType(Params...)>& t_function) 
		{
			m_listeners.push_back(t_function);
		}

		inline bool removeListener(const std::function<ReturnType(Params...)>& t_function) 
		{
			for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
			{
				if (*it == t_function)
				{
					m_listeners.erase(it);
					return true;
				}
			}
			return false;
		}

		inline void clear() 
		{
			m_listeners.clear();
		}

	private:

		std::vector<std::function<ReturnType(Params...)>> m_listeners{};
	};

	typedef event_t<void> event;
}