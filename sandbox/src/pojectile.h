/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/entity/component.h>

namespace editor
{
	class Context;
}

class Projectile : public Component
{
public:
	Projectile();

	void update(double deltaTime) override;
	void inspect(editor::Context& context) override;

	void follow(Entity* const target);

private:
	Entity* m_target;
	float m_speed;
};