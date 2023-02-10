/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/player/player_state.h>

#include "game_player_state_generated.h"

CLASS(Type = PlayerState)
class GamePlayerState : public PlayerState
{
public:
	GamePlayerState() = default;
	virtual ~GamePlayerState() = default;

	GENERATED_BODY()

private:
	PROPERTY() int m_xp{ 0 };
};