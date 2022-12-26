/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "editor_settings_generated.h"

CLASS()
struct EditorSettings : public Type
{
	PROPERTY() bool renderWindows{ true };

	GENERATED_BODY()
};