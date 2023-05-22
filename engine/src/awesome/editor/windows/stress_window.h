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
	PrefabAsset m_prefab;
	int m_quantity{ 100 };
	float m_range{ 10.f };
};