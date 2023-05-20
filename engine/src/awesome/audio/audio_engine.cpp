#include "audio_engine.h"

#include <cassert>
#include <miniaudio.h>

#include <awesome/core/logger.h>

#include "audio_module.h"

extern ma_engine* audio_context;

AudioEngine::AudioEngine()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

AudioStreamPtr AudioEngine::stream(const AudioAsset& asset)
{
	const auto& it = m_streams.find(asset.id);
	if (it != m_streams.end())
	{
		return it->second.lock();
	}

	if (audio_context == nullptr)
		return nullptr;

	AudioStreamPtr stream = std::make_shared<AudioStream>(asset);
	if (ma_sound_init_from_file(audio_context, asset.path.string().c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, stream->data()) != MA_SUCCESS)
	{
		ERR_LOG("Audio", "Failed to load the audio asset");
		return nullptr;
	}
	return stream;
}