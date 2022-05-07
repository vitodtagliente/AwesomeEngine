#include "health.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/math/algorithm.h>

void Health::init()
{
	m_value = math::clamp(m_value, min, max);
}

void Health::inspect()
{
	Component::inspect();
	editor::Layout::input("Min", min);
	editor::Layout::input("Max", max);
	editor::Layout::input("Value", m_value);
	editor::Layout::input("Destroy on Death", m_destroyOnDeath);
}

json::value Health::serialize() const
{
	json::value data = Component::serialize();
	data["min"] = min;
	data["max"] = max;
	data["value"] = m_value;
	data["destroyOnDeath"] = m_destroyOnDeath;
	return data;
}

void Health::deserialize(const json::value& data)
{
	Component::deserialize(data);
	min = data.safeAt("min").as_number(0).as_int();
	max = data.safeAt("max").as_number(10).as_int();
	m_value = data.safeAt("value").as_number(10).as_int();
	m_destroyOnDeath = data.safeAt("destroyOnDeath").as_bool(false);
}

void Health::set(int value)
{
	const int lastValue = m_value;
	m_value = math::clamp(value, min, max);
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