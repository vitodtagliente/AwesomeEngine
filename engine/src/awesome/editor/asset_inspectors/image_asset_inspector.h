/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/editor/asset_inspector.h>

#include "image_asset_inspector_generated.h"

CLASS(Type = AssetInspector)
class ImageAssetInspector : public AssetInspector
{
public:
	virtual bool canInspect(int type) const override;
	virtual char* const getTitle() const override;
	virtual void inspect(const AssetRecord& record) override;

	GENERATED_BODY()

private:
	ImageAsset m_asset;
};