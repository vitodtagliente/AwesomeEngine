#include "health.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/math/algorithm.h>

void Health::init()
{
	value = math::clamp(value, min, max);
}

void Health::inspect()
{
	Component::inspect();
	editor::Layout::input("Min", min);
	editor::Layout::input("Max", max);
	editor::Layout::input("Value", value);
}

json::value Health::serialize() const
{
	json::value data = Component::serialize();
	data["min"] = min;
	data["max"] = max;
	data["value"] = value;
	data["destroyOnDeath"] = destroyOnDeath;
	return data;
}

void Health::deserialize(const json::value& data)
{
	Component::deserialize(data);
	min = data.safeAt("min").as_number(0).as_int();
	max = data.safeAt("max").as_number(10).as_int();
	value = data.safeAt("value").as_number(10).as_int();
	destroyOnDeath = data.safeAt("destroyOnDeath").as_bool(false);
}

void Health::set(int v)
{
	value = math::clamp(v, min, max);
}

REFLECT_COMPONENT(Health)