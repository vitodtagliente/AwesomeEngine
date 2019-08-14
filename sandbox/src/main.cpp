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
	std::cout << String::trim("   cioa   ") << "dd" << std::endl;

	Engine::run({ new ShinyGalaxy() });
	return 0;
}