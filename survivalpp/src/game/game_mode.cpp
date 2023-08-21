#include "game_mode.h"

#include "core/allocator.h"
#include "ecs/ecs.h"
#include "gameplay/player.h"
#include "math/algorithm.h"

#include "components/sprite.h"
#include "components/sprite_animator.h"

#include "game_factory.h"

#include "game/data/pawn_definition.h"
#include "game/gameplay/game_player_controller.h"

void GameMode::init()
{
	// TODO: load from json
	PawnDefinition data;
	data.name = "player";
	data.texture = "../data/arthur.png";
	data.stats.hp = 10;
	data.stats.speed = 10.f;

	Entity& entity = GameFactory::pawn(data);
	
	Player& local_player = PlayerManager::local();
	local_player.controller = std::make_unique<GamePlayerController>();
	local_player.controller->possess(&entity);
}

void GameMode::update(const double delta_time)
{
	m_spawner.update(delta_time);
}

void GameMode::render()
{

}
