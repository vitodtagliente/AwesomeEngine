#include "game_factory.h"

#include "ecs/entity.h"

#include "components/rigidbody2d.h"
#include "components/sprite.h"
#include "components/sprite_animator.h"

#include "components/health.h"
#include "components/pawn.h"

Entity& GameFactory::pawn(const PawnDefinition& definition)
{
	Entity& entity = EntityManager::spawn();
	entity.name = definition.name;
	entity.transform.scale = math::vec2(2.f, 2.f);

	Rigidbody2D& body = entity.addComponent<Rigidbody2D>();
	body.gravityScale = 0.f;

	Sprite& sprite = entity.addComponent<Sprite>();
	sprite.texture = definition.texture;
	sprite.rect = graphics::TextureRect(0.f, 0.f, 1.f / 8, 1.f / 6);

	auto& animator = entity.addComponent<SpriteAnimator>();
	SpriteAnimation idle;
	idle.loop = true;
	for (int i = 0; i < 4; ++i)
	{
		SpriteAnimationFrame frame;
		frame.duration = 0.2f;
		frame.rect = graphics::TextureRect(1.f / 8 * i, 0.f, 1.f / 8, 1.f / 6);
		idle.frames.push_back(frame);
	}
	SpriteAnimation walk;
	walk.loop = true;
	for (int i = 0; i < 4; ++i)
	{
		SpriteAnimationFrame frame;
		frame.duration = 0.2f;
		frame.rect = graphics::TextureRect(1.f / 8 * i, 1.f / 6 * 2, 1.f / 8, 1.f / 6);
		walk.frames.push_back(frame);
	}
	animator.animations.insert(std::make_pair("idle", idle));
	animator.animations.insert(std::make_pair("walk", walk));

	Pawn& pawn = entity.addComponent<Pawn>();
	pawn.stats = definition.stats;
	
	Health& health = entity.addComponent<Health>();
	health.max = health.value = definition.stats.hp;

	return entity;
}
