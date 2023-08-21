#pragma once

#include "ecs/ecs.h"

#include "components/sprite_animator.h"

class SpriteAnimatorSystem : public System<SpriteAnimator>
{
protected:
	virtual void process(double delta_time, SpriteAnimator& data);
};