/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/singleton.h>

#include "entity.h"

class SceneGraph final : public Singleton<SceneGraph>
{
public:
	SceneGraph() = default;

	Entity* const root() { return &m_root; }

private:
	Entity m_root;
};