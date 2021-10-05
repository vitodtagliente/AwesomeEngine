/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "panel.h"

class Entity;

class SceneTreeViewer : Panel
{
public:
	SceneTreeViewer();

	virtual void render() override;

	inline Entity* const getSelectedEntity() const { return m_selectedEntity; }

private:

	Entity* m_selectedEntity;
};