#include "camera_controller2d_component.h"

#include <awesome/engine/input.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

void CameraController2DComponent::update(double deltaTime)
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
			math::vec2 direction = input.getMousePosition() - m_dragPosition.value();
			math::vec2 amount = direction * speed * static_cast<float>(deltaTime);
			getOwnerTransform().position += math::vec3(amount.x, -amount.y, 0.0f);
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
		math::vec3& scale = getOwnerTransform().scale;
		scale.x = scale.y = math::clamp(scale.x + zoomSpeed * static_cast<float>(deltaTime) * -wheelPosition.y, 0.1f, 3.0f);
	}
}