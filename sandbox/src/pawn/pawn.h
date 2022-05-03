/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/components/sprite_animator.h>
#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

class Pawn : public Component
{
public:
	Pawn() = default;
	virtual ~Pawn() = default;

	inline const math::vec3& getDirection() const { return m_direction; }

	void move(const math::vec3& direction);

	virtual void init() override;

	void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	float speed{ 3.0f };

	REFLECT()

private:
	math::vec3 m_direction{ math::vec3::right };
	SpriteAnimator* animator;
};