/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "pawn.h"
#include "combat_controller.h"

class PawnController : public Component
{
public:
	PawnController() = default;
	virtual ~PawnController() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	REFLECT()

private:
	CombatController* m_combat{ nullptr };
	Pawn* m_pawn{ nullptr };
};