/// Copyright (c) Vito Domenico Tagliente
#pragma once

class EngineModule
{
public:
	EngineModule() = default;
	virtual ~EngineModule() = default;

	virtual void startup() {}
	virtual void shutdown() {}
	virtual void update(double /*deltaTime*/) {}
	virtual void preRendering() {}
	virtual void render() {}
	virtual void postRendering() {}
};