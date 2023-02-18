/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>
#include <awesome/serialization/entity_serialization.h>

#include "game.h"

void test()
{
	Entity entity;
	json::value e = serialize(entity);
}

int main()
{
	test();
	Engine& engine = Engine::instance();
	engine.init({ new Game() });
	const int result = engine.run();
	return result;
}