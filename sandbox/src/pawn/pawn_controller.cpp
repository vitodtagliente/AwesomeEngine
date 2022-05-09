#include "pawn_controller.h"

#include <awesome/application/input.h>
#include <awesome/entity/entity.h>
#include <awesome/math/vector3.h>

void PawnController::init()
{
	m_combat = getOwner()->findComponent<CombatController>();
	m_pawn = getOwner()->findComponent<Pawn>();
}

void PawnController::update(const double deltaTime)
{
	if (!m_pawn) return;

	Input& input = Input::instance();
	const math::vec3 direction(input.getAxis(KeyCode::A, KeyCode::D), input.getAxis(KeyCode::S, KeyCode::W), 0.0f);
	m_pawn->move(direction, deltaTime);

	if (input.isKeyPressed(KeyCode::Space))
	{
		m_pawn->dash(deltaTime);
	}

	if (m_combat && input.isKeyPressed(KeyCode::MouseLeftButton))
	{
		m_combat->attack();
	}
}

REFLECT_COMPONENT(PawnController)