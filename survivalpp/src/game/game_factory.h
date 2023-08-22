#pragma once

#include <string>

#include "ecs/entity.h"

#include "math/vector2.h"

#include "game/components/bullet.h"
#include "game/data/pawn_definition.h"

struct GameFactory
{
	static Entity& pawn(const PawnDefinition& definition);
	static Entity& bullet(const EntityPtr& owner, const math::vec2& direction);
};