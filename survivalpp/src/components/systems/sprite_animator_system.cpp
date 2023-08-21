#include "sprite_animator_system.h"

void SpriteAnimatorSystem::process(const double delta_time, SpriteAnimator& animator)
{
	animator.update(delta_time);
}
