/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>

class GraphicsModule : public EngineModule
{
public:
	virtual bool startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render() override;
	virtual void postRendering() override;
};