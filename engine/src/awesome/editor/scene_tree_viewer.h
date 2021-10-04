/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "panel.h"

class World;

class SceneTreeViewer : Panel
{
public:
	SceneTreeViewer();

	void init(World* const world);
	virtual void render() override;

private:
	World* m_world;
};