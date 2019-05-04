/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <iostream>
#include "sandbox_game.h"

using namespace awesome;
using namespace std;

int main()
{
	Engine::run({ new SandboxGame() });
	return 0;
}