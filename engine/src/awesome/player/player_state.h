/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "player_state_generated.h"

CLASS(Category = PlayerState)
class PlayerState : public Component
{
public:
	PlayerState() = default;
	virtual ~PlayerState() = default;

	PROPERTY() std::string gamertag;

	GENERATED_BODY()
};