/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "ecs/system.h"

class EngineModule
{
public:
	EngineModule() = default;
	virtual ~EngineModule() = default;

	virtual bool startup(SystemRegistry& render_systems, SystemRegistry& update_systems) { return true; }
	virtual void shutdown() {}
	virtual void update(double /*deltaTime*/) {}
	virtual void preRendering() {}
	virtual void render() {}
	virtual void postRendering() {}
};