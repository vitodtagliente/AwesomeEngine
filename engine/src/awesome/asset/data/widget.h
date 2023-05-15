/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/ui/control.h>

#include "widget_generated.h"

CLASS()
struct Widget : public IType
{
	PROPERTY() Control control;

	GENERATED_BODY()
};