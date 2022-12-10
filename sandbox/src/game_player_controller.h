/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/player/player_controller.h>

#include "game_player_controller_generated.h"

CLASS(Category = PlayerController)
class GamePlayerController : public PlayerController
{
public:
	GamePlayerController() = default;
	virtual ~GamePlayerController() = default;

	GENERATED_BODY()
};