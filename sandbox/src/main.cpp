/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>
#include <awesome/components/sprite_renderer_component.h>

#include "game.h"

int main()
{
	Engine& engine = Engine::instance();
	engine.init({ new Game() });
	const int result = engine.run();
	return result;
}