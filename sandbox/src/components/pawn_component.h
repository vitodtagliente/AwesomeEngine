/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/body2d_component.h>
#include <awesome/component/sprite_animator_component.h>
#include <awesome/component/sprite_renderer_component.h>
#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

CLASS()
class PawnComponent : public Component
{
public:
	PawnComponent() = default;
	virtual ~PawnComponent() = default;

	inline const math::vec3& getDirection() const { return m_direction; }

	void move(const math::vec3& direction, double deltaTime);
	void dash(double deltaTime);

	virtual void init() override;

	void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	float speed{ 3.0f };
	float dashSpeed{ 12.0f };

	GENERATED_BODY()

private:
	SpriteAnimatorComponent* m_animator{ nullptr };
	Body2dComponent* m_body{ nullptr };
	math::vec3 m_direction{ math::vec3::right };
	SpriteRendererComponent* m_renderer{ nullptr };
};