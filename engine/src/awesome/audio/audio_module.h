/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>

class AudioModule : public EngineModule
{
public:
	virtual bool startup() override;
	virtual void shutdown() override;
	virtual void update(double /*deltaTime*/) override;
};