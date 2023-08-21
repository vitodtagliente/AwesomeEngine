#include "enemy_system.h"

#include "gameplay/player.h"

void EnemySystem::pre_run(double delta_time)
{
	m_player_entity = PlayerManager::local().controller->entity();
}

void EnemySystem::process(const double delta_time, Pawn& pawn)
{
	if (pawn.type != PawnType::Enemy) return;

	if (!m_player_entity)
	{
		pawn.entity()->queue_free();
		return;
	}

	const math::vec2 direction = (m_player_entity->transform.position - pawn.entity()->transform.position).normalize();
	pawn.move(direction);
}
