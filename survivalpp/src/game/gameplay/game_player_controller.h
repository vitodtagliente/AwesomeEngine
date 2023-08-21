#pragma once

#include "gameplay/player.h"

struct GamePlayerController : public PlayerController
{
	virtual void update(double delta_time) override;
};