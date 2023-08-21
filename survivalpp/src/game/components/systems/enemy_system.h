#pragma once

#include "ecs/ecs.h"

#include "game/components/pawn.h"

class EnemySystem : public System<Pawn>
{
protected:
	virtual void pre_run(double delta_time);
	virtual void process(double delta_time, Pawn& pawn);

private:
	EntityPtr m_player_entity;
};