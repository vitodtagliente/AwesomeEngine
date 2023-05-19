#include "audio_module.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <awesome/core/logger.h>

ma_engine* audio_context{ nullptr };

AudioModule::AudioModule()
{
	s_instance = this;
}

bool AudioModule::startup()
{
	ma_engine_config config = ma_engine_config_init();
	config.listenerCount = 1;

	audio_context = new ma_engine();
	const bool result = ma_engine_init(&config, audio_context) == MA_SUCCESS;
	if (!result)
	{
		ERR_LOG("Audio", "Failed to initialize the audio module");
	}
	return result;
}

void AudioModule::shutdown()
{
	ma_engine_uninit(audio_context);
	delete audio_context;
}

void* const AudioModule::context() const
{
	return static_cast<void*>(audio_context);
}