/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/camera.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

namespace component
{
	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera() = default;

		virtual void update(double) override;

		virtual math::vec3 screenToWorldCoords(const math::vec2& point);

		static Camera* const main();

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		graphics::Color color;

		PROTO()

	protected:
		std::unique_ptr<graphics::Camera> m_data;
	};
}