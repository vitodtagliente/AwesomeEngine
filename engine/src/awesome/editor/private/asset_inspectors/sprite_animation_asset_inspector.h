/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/editor/asset_inspector.h>

class SpriteAnimationAssetInspector : public AssetInspector
{
public:
	virtual bool canInspect(int type) const override;
	virtual char* const getTitle() const override;
	virtual void inspect(const AssetRecord& record) override;
	virtual void update(double deltaTime) override;

private:
	SpriteAnimationAsset m_asset;
	int m_frameIndex;
	double m_timeLeft;
};