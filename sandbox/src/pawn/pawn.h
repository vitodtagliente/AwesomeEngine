/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/components/body2d.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

class Pawn : public Component
{
public:
	Pawn() = default;
	virtual ~Pawn() = default;

	inline const math::vec3& getDirection() const { return m_direction; }

	void move(const math::vec3& direction, double deltaTime);
	void dash(const math::vec3& direction, double deltaTime);

	virtual void init() override;

	void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	float speed{ 3.0f };
	float dashSpeed{ 12.0f };

	REFLECT()

private:
	SpriteAnimator* m_animator{ nullptr };
	Body2d* m_body{ nullptr };
	math::vec3 m_direction{ math::vec3::right };
	SpriteRenderer* m_renderer{ nullptr };
};