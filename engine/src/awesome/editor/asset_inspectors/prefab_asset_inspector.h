/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/asset_inspector.h>

#include "prefab_asset_inspector_generated.h"

CLASS(Type = AssetInspector)
class PrefabAssetInspector : public AssetInspector
{
public:
	virtual bool canInspect(int type) const override;
	virtual char* const getTitle() const override;
	virtual void inspect(const AssetRecord& record) override;

	GENERATED_BODY()

private:
	PrefabAsset m_asset;
};