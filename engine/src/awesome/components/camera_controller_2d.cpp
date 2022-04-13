#include "camera_controller_2d.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

CameraController2d::CameraController2d()
	: speed(.05f)
	, zoomSpeed(1.f)
	, m_dragPosition(false)
{
}

void CameraController2d::update(double deltaTime)
{
	Input& input = Input::instance();
	if (!m_dragPosition.has_value())
	{
		if (input.isKeyDown(KeyCode::MouseRightButton))
		{
			m_dragPosition = input.getMousePosition();
		}
	}
	else
	{
		if (input.isKeyDown(KeyCode::MouseRightButton))
		{
			vec2 direction = input.getMousePosition() - m_dragPosition.value();
			vec2 amount = direction * speed * static_cast<float>(deltaTime);
			getOwner()->transform.position += vec3(amount.x, -amount.y, 0.0f);
			m_dragPosition = input.getMousePosition();
		}
		else
		{
			m_dragPosition.reset();
		}
	}

	const math::vec2& wheelPosition = input.getDeltaMouseWheelPosition();
	if (wheelPosition.y != 0.f)
	{
		math::vec3& scale = getOwner()->transform.scale;
		scale.x = scale.y = math::clamp(scale.x + zoomSpeed * static_cast<float>(deltaTime) * -wheelPosition.y, 0.1f, 3.0f);
	}
}

void CameraController2d::render(graphics::Renderer* const renderer)
{
	renderer->pushCamera(getOwner()->transform.matrix());
}

json::value CameraController2d::serialize() const
{
	json::value data = Component::serialize();
	data["speed"] = speed;
	data["zoomSpeed"] = zoomSpeed;
	return data;
}

void CameraController2d::deserialize(const json::value& value)
{
	Component::deserialize(value);
	speed = value["speed"].as_number(0.0f).as_float();
	speed = value["zoomSpeed"].as_number(0.0f).as_float();
}

void CameraController2d::inspect()
{
	Component::inspect();
	editor::Layout::input("Speed", speed);
	editor::Layout::input("Zoom speed", zoomSpeed);
}

REFLECT_COMPONENT(CameraController2d)