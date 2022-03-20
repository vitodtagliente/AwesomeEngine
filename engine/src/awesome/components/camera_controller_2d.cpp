#include "camera_controller_2d.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

CameraController2d::CameraController2d()
	: speed(.1f)
	, m_dragPosition(false)
{
}

void CameraController2d::update(double deltaTime)
{
	Input* const input = Input::instance();
	if (!m_dragPosition.has_value())
	{
		if (input->isKeyDown(KeyCode::MouseRightButton))
		{
			m_dragPosition = input->getMousePosition();
		}
	}
	else
	{
		if (input->isKeyDown(KeyCode::MouseRightButton))
		{
			vec2 direction = input->getMousePosition() - m_dragPosition.value();
			vec2 amount = direction * speed * static_cast<float>(deltaTime);
			getOwner()->transform.position += vec3(amount.x, -amount.y, 0.0f);
			m_dragPosition = input->getMousePosition();
		}
		else
		{
			m_dragPosition.reset();
		}
	}
}

void CameraController2d::render(graphics::Renderer* const renderer)
{
	renderer->pushCamera(getOwner()->transform.matrix());
}

void CameraController2d::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("Speed", &speed);
}

REFLECT_IMP(CameraController2d)