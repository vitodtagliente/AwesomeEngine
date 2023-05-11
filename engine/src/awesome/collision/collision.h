/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>
#include <awesome/engine/engine_settings.h>

class Collision : public EngineModule
{
public:
	Collision();

	virtual bool startup() override;
	virtual void shutdown() override;
	virtual void render() override;
	virtual void update(double /*deltaTime*/) override;

private:
	const RendererSettings& m_settings;
};