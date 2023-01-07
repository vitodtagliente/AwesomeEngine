#include "health_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/math/algorithm.h>

void HealthComponent::init()
{
	m_renderer = getOwner()->findComponent<SpriteRendererComponent>();
	if (m_renderer)
	{
		m_colorToRestore = m_renderer->color;
	}
	m_value = math::clamp(m_value, min, max);
	m_timer.stop();
}

void HealthComponent::update(const double deltaTime)
{
	if (m_timer.isTicking())
	{
		m_timer.tick(deltaTime);
		if (m_timer.isExpired())
		{
			if (m_renderer) m_renderer->color = m_colorToRestore;
		}
	}
}

void HealthComponent::setValue(int value)
{
	const int lastValue = m_value;
	m_value = math::clamp(value, min, max);
	if (m_value < lastValue)
	{
		m_timer.reset(m_hitDuration);
		if (m_renderer) m_renderer->color = m_hitColor;
	}
	if (m_destroyOnDeath && lastValue > 0 && m_value == 0)
	{
		getOwner()->queue_destroy();
	}
}

int HealthComponent::getPercentage() const
{
	return 100 / max * m_value;
}

HealthComponent& HealthComponent::operator+=(const int value)
{
	setValue(m_value + value);
	return *this;
}

HealthComponent& HealthComponent::operator-=(const int value)
{
	setValue(m_value - value);
	return *this;
}