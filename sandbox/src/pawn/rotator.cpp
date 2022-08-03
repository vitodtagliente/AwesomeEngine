#include "rotator.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

Rotator::Rotator()
	: speed(math::random(5.0f, 40.0f))
{

}

void Rotator::update(double deltaTime)
{
	math::transform& transform = getOwner()->transform;
	transform.rotation.z = getOwner()->transform.rotation.z;
	transform.rotation.z += speed * static_cast<float>(deltaTime);
	if (transform.rotation.z >= 360.f)
	{
		transform.rotation.z = 0;
	}
}

void Rotator::inspect()
{
	Component::inspect();
	editor::Layout::input("Speed", speed);
}