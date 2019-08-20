#pragma once

/*
	Copyright 2019 Vito Domenico Tagliente. All rights reserved.

	Event Data Type

	- Use case:

		struct Foo
		{
			void print(const std::string& t_str){ ... }
		};

		Foo* foo = new Foo();

		// declare event variable:

		event_t<void, const std::string&> e;

		// add listeners using three ways:

		e.bind(foo, &Foo::print);
		e.bind(std::bind(&Foo::print, foo, std::placeholders::_1));
		e.bind([](const std::string& t_str){
			std::cout << t_str << std::endl;
		});

		// call events:

		e.broadcast("hello");

*/

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

		inline void bind(const std::function<ReturnType(Params...)>& t_function) 
		{
			m_listeners.push_back(t_function);
		}

		template <class ObjectClass>
		inline void bind(ObjectClass* const t_object, ReturnType(ObjectClass::* t_method)(Params...))
		{
			m_listeners.push_back(
				[=](auto&& ... args) { return (t_object->*t_method)(std::forward<decltype(args)>(args)...); }
			);
		}

		template <class ObjectClass>
		inline void bind(const ObjectClass* const t_object, ReturnType(ObjectClass::* t_method)(Params...) const)
		{
			m_listeners.push_back(
				[=](auto&& ... args) { return (t_object->*t_method)(std::forward<decltype(args)>(args)...); }
			);
		}

		inline bool unbind(const std::function<ReturnType(Params...)>& t_function) 
		{
			for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
			{
				const std::function<ReturnType(Params...)>& it_function = *it;
				if (it_function.target_type() == t_function.target_type())
				{
					m_listeners.erase(it);
					return true;
				}
			}
			return false;
		}

		template <class ObjectClass>
		inline void unbind(ObjectClass* const t_object, ReturnType(ObjectClass::* t_method)(Params...))
		{
			unbind(
				[=](auto&& ... args) { return (t_object->*t_method)(std::forward<decltype(args)>(args)...); }
			);
		}

		template <class ObjectClass>
		inline void unbind(const ObjectClass* const t_object, ReturnType(ObjectClass::* t_method)(Params...) const)
		{
			unbind(
				[=](auto&& ... args) { return (t_object->*t_method)(std::forward<decltype(args)>(args)...); }
			);
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