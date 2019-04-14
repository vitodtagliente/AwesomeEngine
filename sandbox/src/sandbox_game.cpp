#include "sandbox_game.h"
#include <iostream>

using namespace std;

SandboxGame::SandboxGame()
	: Game()
{
}

SandboxGame::~SandboxGame()
{
	Game::~Game();

}

void SandboxGame::init()
{
	Game::init();


}

void SandboxGame::update()
{
	Game::update();

	if (Input* input = Engine::getInstance()->getInput())
	{
		if (input->isKeyPressed(KeyCode::A))
		{
			cout << "A down" << endl;
		}
	}
}

void SandboxGame::uninit()
{
	Game::uninit();


}

void SandboxGame::end()
{
	Game::end();


}