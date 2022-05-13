#include "health.h"

#include <awesome/components/sprite_renderer.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/math/algorithm.h>

void Health::init()
{
	if (m_renderer = getOwner()->findComponent<SpriteRenderer>())
	{
		m_colorToRestore = m_renderer->color;
	}
	m_value = math::clamp(m_value, min, max);
}

void Health::update(const double deltaTime)
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

void Health::inspect()
{
	Component::inspect();
	editor::Layout::input("Min", min);
	editor::Layout::input("Max", max);
	editor::Layout::input("Value", m_value);
	editor::Layout::input("Destroy on Death", m_destroyOnDeath);
	editor::Layout::input("Hit Color", m_hitColor);
	editor::Layout::input("Hit Duration", m_hitDuration);
}

json::value Health::serialize() const
{
	json::value data = Component::serialize();
	data["min"] = min;
	data["max"] = max;
	data["value"] = m_value;
	data["destroyOnDeath"] = m_destroyOnDeath;
	data["hitColor"] = ::serialize(m_hitColor);
	data["hitDuration"] = m_hitDuration;
	return data;
}

void Health::deserialize(const json::value& data)
{
	Component::deserialize(data);
	min = data.safeAt("min").as_number(0).as_int();
	max = data.safeAt("max").as_number(10).as_int();
	m_value = data.safeAt("value").as_number(10).as_int();
	m_destroyOnDeath = data.safeAt("destroyOnDeath").as_bool(false);
	::deserialize(data.safeAt("hitColor"), m_hitColor);
	m_hitDuration = data.safeAt("hitDuration").as_number(.1).as_double();
}

void Health::set(int value)
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
		World::instance().destroy(getOwner());
	}
}

int Health::getPercentage() const
{
	return 100 / max * m_value;
}

Health& Health::operator+=(const int value)
{
	set(m_value + value);
	return *this;
}

Health& Health::operator-=(const int value)
{
	set(m_value - value);
	return *this;
}

REFLECT_COMPONENT(Health)