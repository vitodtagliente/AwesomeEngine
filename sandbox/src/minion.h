/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/entity/component.h>

#include "path_navigator.h"

namespace editor
{
	class Context;
}

class Minion : public Component
{
public:
	Minion();

	void init() override;
	void update(double deltaTime) override;
	void inspect(editor::Context& context) override;

private:
	PathNavigator m_navigator;
	float m_speed;
};