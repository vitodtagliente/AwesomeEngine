/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include "game.h"

int main()
{
	Game* const game = new Game();
	Application app({ game });
	const int result = app.run();
	delete game;
	return result;
}