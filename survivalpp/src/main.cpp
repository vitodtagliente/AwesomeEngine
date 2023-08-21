#include "engine/engine.h"
#include "game.h"

Game game;

int main(int argc, char* argv[]) 
{
	Engine& engine = Engine::instance();
	engine.init({ new Game() });
	const int result = engine.run();
	return result;
}