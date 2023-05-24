#include "audio_asset_inspector.h"

#include <awesome/audio/audio_engine.h>
#include <awesome/editor/editor_ui.h>

bool AudioAssetInspector::canInspect(int type) const
{
	return type == AudioAsset::Type;
}

char* const AudioAssetInspector::getTitle() const
{
	return "Audio";
}

void AudioAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = AudioAsset(record.id);
		m_asset.load([this]() {
			m_stream = AudioEngine::instance()->stream(m_asset);
		});
	}

	EditorUI::Audio::player(m_stream);
}