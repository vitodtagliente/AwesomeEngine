/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/application/application_module.h>

namespace graphics
{
	class Renderer2D;
}

class World;

class UI : public ApplicationModule
{
public:
	UI();

	virtual void startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render(World* const world, graphics::Renderer2D* const renderer) override;
	virtual void postRendering() override;
	virtual void update(double deltaTime) override;

	static UI* const instance() { return s_instance; }

private:
	static UI* s_instance;
};