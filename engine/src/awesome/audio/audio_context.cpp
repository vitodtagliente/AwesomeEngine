#include "audio_context.h"

bool AudioContext::load(const std::filesystem::path& path, Sound& sound)
{
    ma_result result = ma_sound_init_from_file(&m_engine, path.string().c_str(), 0, nullptr, nullptr, &sound);
    return result == MA_SUCCESS;
}

void AudioContext::play(Sound& sound)
{
    ma_sound_start(&sound);
}