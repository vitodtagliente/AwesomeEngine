/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "minion_controller_component_generated.h"

CLASS(Type = Component)
class MinionControllerComponent : public Component
{
public:
	MinionControllerComponent() = default;
	virtual ~MinionControllerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	bool findTarget();

	class PawnComponent* m_pawn{ nullptr };
	class Entity* m_target{ nullptr };
	PROPERTY() std::string m_targetTag;
};