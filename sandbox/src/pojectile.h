/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/entity/component.h>

class Projectile : public Component
{
public:
	Projectile();

	void update(double deltaTime) override;

	void follow(Entity* const target);

private:
	Entity* m_target;
	float m_speed;
};