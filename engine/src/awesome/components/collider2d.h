/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>

REFLECT_ENUM(Collider2dType,
	Circle,
	Rect
)

namespace graphics
{
	class Renderer;
}

class Collider2d : public Component
{
public:
	typedef Collider2dType Type;

	Collider2d() = default;
	virtual ~Collider2d() = default;

	void render(graphics::Renderer* const renderer) override;

	bool collide(const Collider2d& other) const;

	std::function<void(const Collider2d&)> onTrigger;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	bool isTrigger{ false };

	REFLECT()

private:
	Type m_type{ Type::Rect };
	math::vec2 m_rectSize{ 1.0f, 1.0f };
	float m_circleSize{ 1.0f };
};