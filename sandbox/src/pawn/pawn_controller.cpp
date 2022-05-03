#include "pawn_controller.h"

#include <awesome/application/input.h>
#include <awesome/entity/entity.h>
#include <awesome/math/vector3.h>

void PawnController::init()
{
	m_pawn = getOwner()->findComponent<Pawn>();
}

void PawnController::update(const double deltaTime)
{
	if (!m_pawn) return;

	Input& input = Input::instance();
	const math::vec3 direction(input.getAxis(KeyCode::A, KeyCode::D), input.getAxis(KeyCode::S, KeyCode::W), 0.0f);
	m_pawn->move(direction * static_cast<float>(deltaTime));
}

REFLECT_COMPONENT(PawnController)