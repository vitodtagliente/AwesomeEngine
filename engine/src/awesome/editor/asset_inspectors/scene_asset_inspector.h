/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/scene_asset.h>
#include <awesome/editor/asset_inspector.h>

#include "scene_asset_inspector_generated.h"

CLASS(Type = AssetInspector)
class SceneAssetInspector : public AssetInspector
{
public:
	virtual bool canInspect(int type) const override;
	virtual char* const getTitle() const override;
	virtual void inspect(const AssetRecord& record) override;

	GENERATED_BODY()

private:
	SceneAsset m_asset;
};