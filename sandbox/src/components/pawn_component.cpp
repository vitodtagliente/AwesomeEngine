#include "pawn_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void PawnComponent::move(const math::vec3& direction, const double deltaTime)
{
	if (m_animator
		&& m_animator->isPlaying()
		&& (m_animator->getPlayingAnimation() != "idle" && m_animator->getPlayingAnimation() != "walk"))
	{
		return;
	}

	if (direction != math::vec3::zero)
	{
		m_direction = direction;
		if (m_renderer) m_renderer->flipX = m_direction.x < 0.f;
	}

	if (m_body) m_body->move(direction * speed * static_cast<float>(deltaTime));
	if (m_animator) m_animator->play(direction != math::vec3::zero ? "walk" : "idle", true);
}

void PawnComponent::dash(const double deltaTime)
{
	if (m_body == nullptr) return;

	m_body->move(m_direction * dashSpeed * static_cast<float>(deltaTime));
}

void PawnComponent::init()
{
	m_animator = getOwner()->findComponent<SpriteAnimatorComponent>();
	m_body = getOwner()->findComponent<Body2dComponent>();
	m_renderer = getOwner()->findComponent<SpriteRendererComponent>();
}