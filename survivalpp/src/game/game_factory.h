#pragma once

#include <string>

#include "ecs/entity.h"

#include "game/data/pawn_definition.h"

struct GameFactory
{
	static Entity& pawn(const PawnDefinition& definition);
};