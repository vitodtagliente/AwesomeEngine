/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/audio_asset.h>
#include <awesome/audio/audio_stream.h>
#include <awesome/editor/asset_inspector.h>

class AudioAssetInspector : public AssetInspector
{
public:
	virtual bool canInspect(int type) const override;
	virtual char* const getTitle() const override;
	virtual void inspect(const AssetRecord& record) override;

private:
	AudioAsset m_asset;
	AudioStreamPtr m_stream;
};