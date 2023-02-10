/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>

class Game : public EngineModule
{
public:
	void startup() override;
	void shutdown() override;
};