/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/application/application_module.h>

namespace graphics
{
	class Renderer2D;
}

class Graphics : public ApplicationModule
{
public:
	struct Performances
	{
		int drawCalls{ 0 };
	};

	Graphics();

	virtual void startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render() override;
	virtual void postRendering() override;

	static Graphics* const instance() { return s_instance; }

	Performances performances;
	std::unique_ptr<graphics::Renderer2D> renderer;

private:
	static Graphics* s_instance;
};