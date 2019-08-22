/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <iostream>
#include <functional>
#include "sandbox_game.h"
#include "shinygalaxy_game.h"

using namespace awesome;

class Foo
{
public:

	Foo(int t_i)
		: m_i(t_i)
	{

	}

	void foo()
	{
		std::cout << "foo\n";
	}

	void print(const std::string& t_str)
	{
		std::cout << t_str << m_i << std::endl;
	}

private:

	int m_i;
};

int main()
{
	Foo* foo = new Foo(3);

	event_t<const std::string&> e;
	e.bind([](const std::string& t_str) {
		std::cout << "hello " << t_str << std::endl;
	});
	e.bind(foo, &Foo::print);
	e.unbind(foo, &Foo::print);
	e.broadcast("world");

	// Engine::run({ new ShinyGalaxy() });
	return 0;
}