/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <iostream>
#include "sandbox_game.h"
#include "shinygalaxy_game.h"

using namespace awesome;

int main()
{
	Engine::run({ new ShinyGalaxy() });
	return 0;
}