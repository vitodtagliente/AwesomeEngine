/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>
#include <awesome/math/matrix4.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/scene/component.h>

#include "camera_component_generated.h"

namespace graphics
{
	class Renderer;
}

CLASS()
class CameraComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double deltaTime) override;

	const math::mat4& view() const { return m_view; }
	virtual math::vec3 screenToWorldCoords(const math::vec2& point);

	static CameraComponent* const main();

	PROPERTY() graphics::Color color{ graphics::Color::Black };

	GENERATED_BODY()

protected:
	graphics::Renderer* m_renderer{ nullptr };
	math::mat4 m_view{ math::mat4::identity };

	static CameraComponent* s_instance;
};