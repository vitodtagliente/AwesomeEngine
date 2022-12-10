/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>

#include "player_state_generated.h"

CLASS(Category = PlayerState)
class PlayerState : public Type
{
public:
	PlayerState() = default;
	virtual ~PlayerState() = default;

	virtual void init() {}
	virtual void update(double /*deltaTime*/) {}

	PROPERTY() std::string gamertag;

	GENERATED_BODY()
};