/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/window.h>
#include <awesome/math/vector3.h>

class StressWindow : public Window
{
public:
	virtual char* const getTitle() const override;
	virtual void render() override;

protected:
	math::vec3 m_maxPosition{ 1.f, 1.f, 0.f };
	math::vec3 m_minPosition{ -1.f, -1.f, 0.f };
	PrefabAsset m_prefab;
	int m_quantity{ 100 };
	bool m_randomPosition{ true };
};