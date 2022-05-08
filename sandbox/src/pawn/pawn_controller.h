/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "pawn.h"

class PawnController : public Component
{
public:
	PawnController() = default;
	virtual ~PawnController() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	REFLECT()

private:
	Pawn* m_pawn{ nullptr };
};