#pragma once

/*
	Copyright 2019 Vito Domenico Tagliente. All rights reserved.

	Event Data Type

	- Usage example:

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
		auto handler = e.bind([](const std::string& t_str){
			std::cout << t_str << std::endl;
		});

		// unbind 
		e.unbind(handler);
		e.unbind(foo, &Foo::print);

		// call events:

		e.broadcast("hello");
*/

#include <cassert>
#include <functional>
#include <vector>

namespace awesome
{
	template <typename... Params>
	class event_t
	{
	public:

		using function_t = std::function<void(Params...)>;

		class handler_t
		{
		public:

			handler_t()
			{
				static unsigned int counter = 0;

				m_id = ++counter;
			}

			virtual void execute(Params... t_args) = 0;

			bool operator== (const handler_t& t_handler) const
			{
				return m_id == t_handler.m_id;
			}

			bool operator!= (const handler_t& t_handler) const
			{
				return m_id != t_handler.m_id;
			}

		private:

			unsigned int m_id;

		};

		event_t()
			: m_handlers()
		{

		}

		~event_t()
		{
			for (handler_t* const handler : m_handlers)
			{
				delete handler;
			}
		}

		inline void broadcast(Params... t_args) 
		{
			for (handler_t* const handler : m_handlers) 
			{
				handler->execute(t_args...);
			}
		}

		inline handler_t* const bind(const function_t& t_function)
		{
			handler_t* const handler = new function_handler_t(t_function);
			m_handlers.push_back(handler);
			return handler;
		}

		template <class T>
		inline handler_t* const bind(T* const t_instance, void (T::*method_name)(Params...))
		{
			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				if (method_handler_t<T>* method_handler = dynamic_cast<method_handler_t<T>*>(*it))
				{
					assert(!(method_handler->instance == t_instance && method_handler->method == method_name)
						&& "method already binded");
				}
			}
			handler_t* const handler = new method_handler_t(t_instance, method_name);
			m_handlers.push_back(handler);
			return handler;
		}

		template <class T>
		inline handler_t* const bind(const T* const t_object, void(T::* t_method)(Params...) const)
		{
			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				if (method_handler_t<T>* method_handler = dynamic_cast<method_handler_t<T>*>(*it))
				{
					assert(!(method_handler->instance == t_instance && method_handler->method == method_name)
						&& "method already binded");
				}
			}
			handler_t* const handler = new method_handler_t(t_instance, method_name);
			m_handlers.push_back(handler);
			return handler;
		}

		inline bool unbind(handler_t* const t_handler)
		{
			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				if (*it == t_handler)
				{
					delete (*it);
					m_handlers.erase(it);
					return true;
				}
			}
			return false;
		}

		template <class T>
		inline bool unbind(T* const t_instance, void (T::*method_name)(Params...))
		{
			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				if (method_handler_t<T>* method_handler = dynamic_cast<method_handler_t<T>*>(*it))
				{
					if (method_handler->instance == t_instance
						&& method_handler->method == method_name)
					{
						delete (*it);
						m_handlers.erase(it);
						return true;
					}
				}
			}
			return false;
		}

		template <class T>
		inline bool unbind(const T* const t_object, void(T::* t_method)(Params...) const)
		{
			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				if (method_handler_t<T>* method_handler = dynamic_cast<method_handler_t<T>*>(*it))
				{
					if (method_handler->instance == t_instance
						&& method_handler->method == method_name)
					{
						delete (*it);
						m_handlers.erase(it);
						return true;
					}
				}
			}
			return false;
		}

		// clear all handlers
		inline void clear()
		{
			m_handlers.clear();
		}

		// clear all handlers for a specific object
		template <class T>
		inline void clear(T* const t_instance)
		{
			for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				if (method_handler_t<T> * method_handler = dynamic_cast<method_handler_t<T>*>(*it))
				{
					if (method_handler->instance == t_instance)
					{
						delete (*it);
						m_handlers.erase(it);
					}
				}
			}
		}

	private:

		struct function_handler_t : public handler_t
		{
			function_handler_t(const function_t& t_function)
				: handler_t()
				, function(t_function)
			{}
			
			virtual void execute(Params... t_args) override
			{
				if (function)
				{
					function(t_args...);
				}
			}
			
			function_t function;
		};

		template <class T>
		struct method_handler_t : public handler_t
		{
			typedef void (T::*method_t)(Params...);
			
			method_handler_t(T* const t_instance, const method_t& t_method)
				: handler_t()
				, instance(t_instance)
				, method(t_method)
			{}

			virtual void execute(Params... t_args) override
			{
				if (instance && method)
				{
					std::invoke(method, instance, t_args...);
				}
			}

			T* instance;
			method_t method;
		};

		std::vector<handler_t*> m_handlers{};
	};

	typedef event_t<> event;
}