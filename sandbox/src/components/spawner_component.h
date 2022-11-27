/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "spawner_component_generated.h"

CLASS(Category = Component)
class SpawnerComponent : public Component
{
public:
	SpawnerComponent() = default;
	virtual ~SpawnerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime);

	GENERATED_BODY()

private:

};