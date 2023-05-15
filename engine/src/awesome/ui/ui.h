/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>

#include "ui_graph.h"

class UI : public EngineModule
{
public:
	UI();

	virtual bool startup() override;
	virtual void shutdown() override;
	virtual void render() override;
	virtual void update(double deltaTime) override;

private:
	UIGraph& m_canvas;
};