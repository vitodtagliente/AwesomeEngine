/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/application/application_module.h>

namespace graphics
{
	class Context;
	class Renderer;
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
	std::unique_ptr<graphics::Renderer> renderer;

private:
	std::unique_ptr<graphics::Context> m_context;

	static Graphics* s_instance;
};