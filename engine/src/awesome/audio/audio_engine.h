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
	AudioStreamPtr stream(const AudioAsset& asset);

	static AudioEngine* const instance() { return s_instance; }

private:	
	std::map<uuid, std::weak_ptr<AudioStream>> m_streams;

	static inline AudioEngine* s_instance{ nullptr };
};