/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>

REFLECT_ENUM(Collider2DType,
	Box,
	Circle
)

namespace graphics
{
	class Renderer;
}

class Collider2D : public Component
{
public:
	typedef Collider2DType Type;

	Collider2D() = default;
	virtual ~Collider2D() = default;

	void render(graphics::Renderer* const renderer) override;

	bool collide(Collider2D& other) const;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()

private:
	Type m_type{ Type::Box };
	math::vec2 m_boxSize{ 1.0f, 1.0f };
	float m_circleSize{ 1.0f };
};