/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/ui/control.h>

#include "user_interface_generated.h"

CLASS()
struct UserInterface : public IType
{
	PROPERTY() std::vector<std::unique_ptr<Control>> controls;

	GENERATED_BODY()
};