/// Copyright (c) Vito Domenico Tagliente
#pragma once

/*
Event Data Type
Usage example:

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

#include <functional>
#include <vector>

template <typename... Args>
class event_t
{
public:
	using function_t = std::function<void(Args...)>;

	inline void bind(const function_t& callback)
	{
		m_callbacks.push_back(callback);
	}

	inline void clear()
	{
		m_callbacks.clear();
	}

	inline void invoke(Args... args)
	{
		for (auto& callback : m_callbacks)
		{
			callback(args...);
		}
	}

private:
	std::vector<function_t> m_callbacks;
};

typedef event_t<> event;