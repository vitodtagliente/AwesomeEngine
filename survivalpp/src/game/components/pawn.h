#pragma once

#include <string>

#include "ecs/component.h"
#include "ecs/component_ptr.h"

#include "math/vector2.h"

#include "game/data/stats.h"

#include "health.h"
#include "components/rigidbody2d.h"
#include "components/sprite.h"
#include "components/sprite_animator.h"

enum PawnType
{
	Enemy,
	Nesus,
	Character
};

class Pawn : public Component
{
public:
	virtual void init() override;

	void aim(const math::vec2& direction);
	void move(const math::vec2& direction);

	Stats stats;
	PawnType type{ PawnType::Enemy };
	Sprite sprite;
	SpriteAnimator sprite_animator;
private:
	ComponentPtr<Rigidbody2D> m_body;
	ComponentPtr<Health> m_health;
	ComponentPtr<Sprite> m_sprite;
	ComponentPtr<SpriteAnimator> m_sprite_animator;
};
