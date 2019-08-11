/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <direct.h>
#include "sandbox_game.h"
#include "shinygalaxy_game.h"

using namespace awesome;

int main()
{
	// filesystem tests
	std::cout << Directory::getCurrentDirectory() << std::endl;
	std::cout << Path::combine("ciao", "allora") << std::endl;

	Engine::run({ new ShinyGalaxy() });
	return 0;
}