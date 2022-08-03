/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

namespace component
{
	class Body2d : public Component
	{
	public:
		Body2d() = default;
		virtual ~Body2d() = default;

		virtual void init() override;

		void move(const math::vec2& amount);
		void move(const math::vec3& amount);

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		PROTO()

	private:
		class Collider2d* m_collider{ nullptr };
	};
}