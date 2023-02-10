/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "pawn_component.h"

#include "pawn_controller_component_generated.h"

CLASS(Type = Component)
class PawnControllerComponent : public Component
{
public:
	PawnControllerComponent() = default;
	virtual ~PawnControllerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	PawnComponent* m_pawn{ nullptr };
};