#include "game_player_controller.h"

#include <iostream>

#include "ecs/entity.h"
#include "engine/input.h"
#include "graphics/renderer.h"

#include "game/components/pawn.h"

void GamePlayerController::update(const double delta_time)
{
	if (!m_entity) return;

	Input& input = Input::instance();
	const float horizontal = input.getAxis(KeyCode::A, KeyCode::D);
	const float vertical = input.getAxis(KeyCode::S, KeyCode::W);

	math::vec2 move_direction(horizontal, vertical);
	move_direction.normalize();

	Pawn* const pawn = m_entity->findComponent<Pawn>();
	if (pawn)
	{
		pawn->move(move_direction);

		const math::vec2& mouse_position = input.getMousePosition();
		const math::vec2& world_mouse_position = graphics::Renderer::instance().screenToWorld(mouse_position);
		const math::vec2& entity_position = m_entity->transform.position;
		math::vec2 aim_direction = (world_mouse_position - entity_position).normalize();
		pawn->aim(aim_direction);

		if (input.isKeyDown(KeyCode::MouseLeftButton))
		{
			pawn->attack();
		}
	}
}
