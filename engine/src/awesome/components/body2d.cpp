#include "body2d.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

json::value Body2d::serialize() const
{
	json::value data = Component::serialize();

	return data;
}

void Body2d::deserialize(const json::value& value)
{
	Component::deserialize(value);

}

void Body2d::inspect()
{
	Component::inspect();

}

REFLECT_COMPONENT(Body2d)