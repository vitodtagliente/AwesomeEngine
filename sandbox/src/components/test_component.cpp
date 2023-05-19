#include "test_component.h"

#include <awesome/components/rigidbody2d_component.h>
#include <awesome/components/sprite_animator_component.h>
#include <awesome/components/sprite_renderer_component.h>
#include <awesome\ecs\entities_coordinator.h>
#include <awesome/engine/input.h>
#include <awesome/scene/entity.h>

void TestComponent::init()
{
	//m_body = getOwner()->findComponent<Rigidbody2DComponent>();
	m_animator = getOwner()->findComponent<SpriteAnimatorComponent>();
	m_sprite = getOwner()->findComponent<SpriteRendererComponent>();
}

void TestComponent::update(const double deltaTime)
{
	//if (m_body == nullptr) return;
	auto& body = EntitiesCoordinator::instance().GetComponent<Rigidbody2DComponent>(getOwner()->storage_id);
	Input& input = Input::instance();
	const float h = input.getAxis(KeyCode::A, KeyCode::D);
	const float v = input.getAxis(KeyCode::S, KeyCode::W);
	const math::vec3 direction = math::vec3(h, v, 0.f);
	body.move(direction * speed * static_cast<float>(deltaTime));

	m_animator->play(direction.magnitude() > 0.f ? "walk" : "idle");
	m_sprite->flipX = h < 0.f;
}