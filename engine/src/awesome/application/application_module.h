/// Copyright (c) Vito Domenico Tagliente
#pragma once

namespace graphics
{
	class Renderer2D;
}

class World;

class ApplicationModule
{
public:
	ApplicationModule() = default;
	virtual ~ApplicationModule() = default;

	virtual void startup() {}
	virtual void shutdown() {}
	virtual void update(double /*deltaTime*/) {}
	virtual void preRendering() {}
	virtual void render(World* const /*world*/, graphics::Renderer2D* const /*renderer*/) {}
	virtual void postRendering() {}
};