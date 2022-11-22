/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "minion_controller_component_generated.h"

CLASS(Category = Component)
class MinionControllerComponent : public Component
{
public:
	MinionControllerComponent() = default;
	virtual ~MinionControllerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	bool findNexus();

	class PawnComponent* m_pawn{ nullptr };
};