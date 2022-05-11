#include "sprite_fsm.h"

#include <awesome/components/sprite_animator.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void SpriteFsm::init()
{
	m_animator = getOwner()->findComponent<SpriteAnimator>();
}

void SpriteFsm::update(const double /*deltaTime*/)
{

}

json::value SpriteFsm::serialize() const
{
	json::value data = Component::serialize();
	return data;
}

void SpriteFsm::deserialize(const json::value& value)
{
	Component::deserialize(value);

	uuid spriteId = uuid::Invalid;
}

void SpriteFsm::inspect()
{
	Component::inspect();
}

REFLECT_COMPONENT(SpriteFsm)