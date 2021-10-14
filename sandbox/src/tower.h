/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/timer.h>
#include <awesome/entity/component.h>

#include "target_finder.h"

namespace editor
{
	class Context;
}

namespace graphics
{
	class Renderer;
}

class Tower : public Component
{
public:
	Tower();

	void init() override;
	void update(double deltaTime) override;
	void render(graphics::Renderer& renderer) override;
	void inspect(editor::Context& context) override;

private:
	TargetFinder m_finder;
	Timer m_timer;
};