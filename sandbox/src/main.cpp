/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <cassert>
#include <iostream>
#include <memory>
#include <functional>
#include "sandbox_game.h"
#include "shinygalaxy_game.h"

using namespace awesome;

class Foo
{
public:

	Foo() = default;
	Foo(const int t_a)
		: a(t_a)
	{

	}

	void println(const std::string& t_str) const
	{
		std::cout << t_str << "." << a << std::endl;
	}

private:

	int a;
};

class Foo1 : public Foo {};

template <typename T>
class singleton_ptr
{
public:

	template <typename... Args>
	static singleton_ptr make(Args... t_args)
	{
		assert(m_instance == nullptr);
		m_instance = new T(std::forward<Args>(t_args)...);
		return {};
	}

	template <typename... Args>
	static singleton_ptr get(Args... t_args)
	{
		if (m_instance == nullptr)
		{
			return make(t_args...);
		}
		return {};
	}

	template <typename... Args>
	singleton_ptr(Args... t_args)
	{
		if (m_instance == nullptr)
		{
			make(t_args...);
		}
	}

	T& operator* ()
	{
		assert(m_instance != nullptr);
		return *m_instance;
	}

	T* operator->() const {
		return m_instance;
	}

private:

	static T* m_instance;
};

template <typename T>
T* singleton_ptr<T>::m_instance = nullptr;

int main()
{
	singleton_ptr<Foo> foo = singleton_ptr<Foo>::make(4);
	singleton_ptr<Foo1>();
	foo->println("ciao");

	Engine::run({ new ShinyGalaxy() });
	return 0;
}