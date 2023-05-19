#include "audio_loader.h"

#include <miniaudio.h>

#include "audio_module.h"

bool AudioLoader::load(const std::filesystem::path& path, Audio& audio)
{
	AudioModule* const module = AudioModule::instance();
	if (module == nullptr) return false;

	ma_engine* context = module->context<ma_engine>();
	if (context == nullptr) return false;

	return ma_sound_init_from_file(context, path.string().c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, &audio) == MA_SUCCESS;
}