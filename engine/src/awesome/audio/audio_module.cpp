#include "audio_module.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <awesome/core/logger.h>

#include "audio_engine.h"

extern ma_engine* audio_context{ nullptr };
AudioEngine* audio_engine{ nullptr };

bool AudioModule::startup()
{
	ma_engine_config config = ma_engine_config_init();
	config.listenerCount = 1;

	audio_context = new ma_engine();
	if (ma_engine_init(&config, audio_context) != MA_SUCCESS)
	{
		ERR_LOG("Audio", "Failed to initialize the audio module");
		return false;
	}
	return audio_engine = new AudioEngine(), true;
}

void AudioModule::shutdown()
{
	delete audio_engine;
	ma_engine_uninit(audio_context);
	delete audio_context;
}