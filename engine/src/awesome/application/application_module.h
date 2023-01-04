/// Copyright (c) Vito Domenico Tagliente
#pragma once

class ApplicationModule
{
public:
	ApplicationModule() = default;
	virtual ~ApplicationModule() = default;

	virtual void startup() {}
	virtual void shutdown() {}
	virtual void update(double /*deltaTime*/) {}
	virtual void preRendering() {}
	virtual void render() {}
	virtual void postRendering() {}
};