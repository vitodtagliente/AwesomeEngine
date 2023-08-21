#include "enemy_spawner.h"

#include "math/algorithm.h"
#include "gameplay/player.h"

#include "game/components/pawn.h"
#include "game/data/pawn_definition.h"
#include "game/game_factory.h"

void EnemySpawner::update(const double delta_time)
{
	m_spawn_timer.tick(delta_time);
	if (m_spawn_timer.isExpired())
	{
		Player& player = PlayerManager::local();
		const math::vec2& pivot = player.controller->entity()->transform.position;

		// TODO: load from json
		PawnDefinition data;
		data.name = "enemy";
		data.texture = "../data/arthur.png";
		data.stats.hp = 3;
		data.stats.speed = 3.f;

		Entity& entity = GameFactory::pawn(data);
		entity.transform.position = pivot + 10.f + math::vec2(math::random(-1.f, 1.f), math::random(-1.f, 1.f)) * math::random(0.f, 10.f);

		m_spawn_timer.reset(1.f);
	}
}
