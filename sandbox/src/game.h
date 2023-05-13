/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>

#include "types.h"

class Game : public EngineModule
{
public:
	bool startup() override;
	void shutdown() override;
};