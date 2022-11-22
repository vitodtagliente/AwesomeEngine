/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

class PlayerState
{
public:
	PlayerState() = default;
	virtual ~PlayerState() = default;

	virtual void init() {}
	virtual void update(double /*deltaTime*/) {}

	std::string gamertag;
};