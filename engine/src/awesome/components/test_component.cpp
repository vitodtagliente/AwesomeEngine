#include "test_component.h"

#include <awesome/components/rigidbody2d_component.h>
#include <awesome/engine/input.h>
#include <awesome/scene/entity.h>

void TestComponent::init()
{
	m_body = getOwner()->findComponent<Rigidbody2DComponent>();
}

void TestComponent::update(const double deltaTime)
{
	if (m_body == nullptr) return;

	Input& input = Input::instance();
	const float h = input.getAxis(KeyCode::A, KeyCode::D);
	const float v = input.getAxis(KeyCode::S, KeyCode::W);
	m_body->move(math::vec3(h, v, 0.f) * speed * static_cast<float>(deltaTime));
}