/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/audio_asset.h>
#include <awesome/core/uuid.h>

#include "audio_stream.h"

class AudioEngine
{
public:
	AudioEngine();

	static AudioEngine* const instance() { return s_instance; }

	void clean();
	void flush();
	void play(const AudioAsset& asset, float volume = 1.f);
	AudioStreamPtr stream(const AudioAsset& asset);

private:	
	static inline AudioEngine* s_instance{ nullptr };
};