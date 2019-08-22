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

		event_t<const std::string&> e;

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
	template <typename... Params>
	class event_t
	{
	public:

		using function_t = std::function<void(Params...)>;

		event_t()
			: m_handlers()
		{

		}

		~event_t()
		{
			for (event_handler_t* const handler : m_handlers)
			{
				delete handler;
			}
		}

		inline void broadcast(Params... t_args) 
		{
			for (event_handler_t* const handler : m_handlers) 
			{
				handler->execute(t_args...);
			}
		}

		inline void bind(const function_t& t_function)
		{
			m_handlers.push_back(new event_handler_t(t_function));
		}

		template <class T>
		inline void bind(T* const t_instance, void (T::*method_name)(Params...))
		{
			m_handlers.push_back(new method_event_handler_t(t_instance, method_name));
		}

		template <class T>
		inline void bind(const T* const t_object, void(T::* t_method)(Params...) const)
		{
			m_handlers.push_back(new method_event_handler_t(t_instance, method_name));
		}

		template <class T>
		inline bool unbind(T* const t_instance, void (T::*method_name)(Params...))
		{
			method_event_handler_t wrapper(t_instance, method_name);

			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				event_handler_t* const handler = *it;
				if (method_event_handler_t<T>* method_handler = dynamic_cast<method_event_handler_t<T>*>(handler))
				{
					if (method_handler == wrapper)
					{
						delete handler;
						m_handlers.erase(it);
						return true;
					}
				}
			}
			return false;
		}

		inline void clear()
		{
			m_handlers.clear();
		}

	private:

		struct event_handler_t
		{
			event_handler_t()
				: function()
			{}

			event_handler_t(const function_t& t_function)
				: function(t_function)
			{}

			function_t function;
			
			virtual void execute(Params... t_args)
			{
				if (function)
				{
					function(t_args...);
				}
			}
		};

		template <class T>
		struct method_event_handler_t : public event_handler_t
		{
			typedef void (T::*method_t)(Params...);

			method_event_handler_t()
				: event_handler_t()
				, instance()
				, method()
			{}

			method_event_handler_t(T* const t_instance, const method_t& t_method)
				: event_handler_t()
				, instance(t_instance)
				, method(t_method)
			{}

			T* instance;
			method_t method;

			virtual void execute(Params... t_args) override
			{
				if (instance && method)
				{
					std::invoke(method, instance, t_args...);
				}
			}
		};

		std::vector<event_handler_t*> m_handlers{};
	};

	typedef event_t<> event;
}