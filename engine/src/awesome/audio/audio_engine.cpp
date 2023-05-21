#include "audio_engine.h"

#include <cassert>
#include <miniaudio.h>

#include <awesome/core/logger.h>

#include "audio_module.h"

extern ma_engine* audio_context;
std::vector<std::unique_ptr<AudioStream>> audio_engine_temps;

AudioEngine::AudioEngine()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void AudioEngine::flush()
{
	audio_engine_temps.erase(std::remove_if(
		audio_engine_temps.begin(),
		audio_engine_temps.end(),
		[](const std::unique_ptr<AudioStream>& audio_stream) -> bool
		{
			return !audio_stream->isPlaying();
		}
		),
		audio_engine_temps.end()
	);

}

void AudioEngine::play(const AudioAsset& asset, const float volume)
{
	AudioStreamPtr audio_stream = stream(asset);
	if (audio_stream)
	{
		audio_stream->stop();
		audio_stream->setLooping(false);
		audio_stream->setVolume(volume);
		audio_stream->play();
	}
}

void AudioEngine::playOneShot(const AudioAsset& asset, const float volume)
{
	std::unique_ptr<AudioStream> audio_stream = std::make_unique<AudioStream>(asset);
	if (ma_sound_init_from_file(audio_context, asset.path.string().c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, audio_stream->data()) != MA_SUCCESS)
	{
		ERR_LOG("Audio", "Failed to load the audio asset");
		return;
	}

	audio_stream->setVolume(volume);
	audio_stream->play();
	audio_engine_temps.push_back(std::move(audio_stream));
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

	AudioStreamPtr audio_stream = std::make_shared<AudioStream>(asset);
	if (ma_sound_init_from_file(audio_context, asset.path.string().c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, audio_stream->data()) != MA_SUCCESS)
	{
		ERR_LOG("Audio", "Failed to load the audio asset");
		return nullptr;
	}
	return audio_stream;
}