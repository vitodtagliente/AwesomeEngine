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
	return data;
}

void Health::deserialize(const json::value& data)
{
	Component::deserialize(data);
	min = data["min"].as_number().as_int();
	max = data["max"].as_number().as_int();
	value = data["value"].as_number().as_int();
}

void Health::set(int v)
{
	value = math::clamp(v, min, max);
}

REFLECT_COMPONENT(Health)