/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <memory>
#include <vector>

#include <awesome/asset/audio_asset.h>
#include <awesome/core/uuid.h>

#include "audio_stream.h"

class AudioEngine
{
public:
	AudioEngine();

	static AudioEngine* const instance() { return s_instance; }

	void flush();
	void play(const AudioAsset& asset, float volume = 1.f);
	void playOneShot(const AudioAsset& asset, float volume = 1.f);
	AudioStreamPtr stream(const AudioAsset& asset);

private:	
	std::map<uuid, std::weak_ptr<AudioStream>> m_streams;

	static inline AudioEngine* s_instance{ nullptr };
};