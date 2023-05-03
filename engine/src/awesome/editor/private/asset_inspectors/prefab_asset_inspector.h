/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/asset_inspector.h>

class PrefabAssetInspector : public AssetInspector
{
public:
	virtual bool canInspect(int type) const override;
	virtual char* const getTitle() const override;
	virtual void inspect(const AssetRecord& record) override;

private:
	PrefabAsset m_asset;
};