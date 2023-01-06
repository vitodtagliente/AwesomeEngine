/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/entity.h>

#include "ui_element_generated.h"

CLASS(Type = Entity)
class UIElement : public Entity
{
public:
	UIElement() = default;
	virtual ~UIElement() = default;

	GENERATED_BODY()
};