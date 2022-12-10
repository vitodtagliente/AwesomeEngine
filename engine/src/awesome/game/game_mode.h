/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "game_mode_generated.h"

CLASS(Category = GameMode)
class GameMode : public Type
{
public:
	GameMode() = default;
	virtual ~GameMode() = default;

	GENERATED_BODY();
};