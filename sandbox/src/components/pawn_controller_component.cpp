#include "pawn_controller_component.h"

#include <awesome/application/input.h>
#include <awesome/entity/entity.h>
#include <awesome/math/vector3.h>

void PawnControllerComponent::init()
{
	m_pawn = getOwner()->findComponent<PawnComponent>();
}

void PawnControllerComponent::update(const double deltaTime)
{
	if (!m_pawn) return;

	Input& input = Input::instance();
	const math::vec3 direction(input.getAxis(KeyCode::A, KeyCode::D), input.getAxis(KeyCode::S, KeyCode::W), 0.0f);
	m_pawn->move(direction, deltaTime);

	if (input.isKeyPressed(KeyCode::Space))
	{
		m_pawn->dash(deltaTime);
	}
}