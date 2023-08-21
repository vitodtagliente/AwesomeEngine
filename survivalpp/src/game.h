/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "engine/engine_module.h"

#include "ecs/system.h"
#include "game/game_mode.h"

class Game : public EngineModule
{
public:
	bool startup(SystemRegistry& render_systems, SystemRegistry& update_systems) override;
	void shutdown() override;
	virtual void update(double /*deltaTime*/) override;
	virtual void render() override;

private:
	GameMode m_mode;
};