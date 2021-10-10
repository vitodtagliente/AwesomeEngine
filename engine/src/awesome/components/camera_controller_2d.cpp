#include "camera_controller_2d.h"

#include <awesome/application/input.h>
#include <awesome/editor/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>
#include <vdtmath/vector2.h>
#include <vdtmath/vector3.h>

CameraController2d::CameraController2d()
	: speed(.001f)
	, m_dragPosition(false)
{
}

void CameraController2d::update(World& world, double deltaTime)
{
	Input* const input = Input::instance();
	if (!m_dragPosition.has_value())
	{
		if (input->isKeyDown(KeyCode::MouseLeftButton))
		{
			m_dragPosition = input->getMousePosition();
		}
	}
	else
	{
		if (input->isKeyDown(KeyCode::MouseLeftButton))
		{
			math::vec2 direction = input->getMousePosition() - m_dragPosition.value();
			const math::vec2 amount = direction.normalize() * static_cast<float>(deltaTime);
			getOwner()->transform.position += math::vec3(amount.x, -amount.y, 0.0f);
		}
		else
		{
			m_dragPosition.reset();
		}
	}
}

void CameraController2d::render(graphics::Renderer& renderer)
{
	renderer.pushCamera(getOwner()->transform.matrix());
}

void CameraController2d::inspect(editor::Context& context)
{
	if (context.collapsingHeader("CameraController2d"))
	{
		context.input("speed", &speed);
	}
}
