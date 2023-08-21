/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "engine/engine_module.h"

class GraphicsModule : public EngineModule
{
public:
	virtual bool startup(SystemRegistry& render_systems, SystemRegistry& update_systems) override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render() override;
	virtual void postRendering() override;
};