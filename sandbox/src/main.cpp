/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>
#include "sandbox_game.h"

using namespace awesome;

int main() 
{
	Engine::run({ new SandboxGame() });
	return 0;
}