/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include "game.h"

int main()
{
	Application app({ new Game() });
	const int result = app.run();
	return result;
}