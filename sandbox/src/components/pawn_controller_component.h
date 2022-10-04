/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "pawn_component.h"
#include "combat_controller_component.h"

#include "pawn_controller_component_generated.h"

CLASS()
class PawnControllerComponent : public Component
{
public:
	PawnControllerComponent() = default;
	virtual ~PawnControllerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	CombatControllerComponent* m_combat{ nullptr };
	PawnComponent* m_pawn{ nullptr };
};