#include "rotator_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

RotatorComponent::RotatorComponent()
	: speed(math::random(5.0f, 40.0f))
{

}

void RotatorComponent::update(double deltaTime)
{
	math::transform& transform = getOwner()->transform;
	transform.rotation.z = getOwner()->transform.rotation.z;
	transform.rotation.z += speed * static_cast<float>(deltaTime);
	if (transform.rotation.z >= 360.f)
	{
		transform.rotation.z = 0;
	}
}