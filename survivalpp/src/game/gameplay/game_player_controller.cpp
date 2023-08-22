#include "game_player_controller.h"

#include "ecs/entity.h"
#include "engine/input.h"

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
		math::vec2 aim_direction = (mouse_position - m_entity->transform.position).normalize();
		pawn->aim(aim_direction);

		if (input.isKeyDown(KeyCode::MouseLeftButton))
		{
			pawn->attack();
		}
	}
}
