#include "audio.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include "audio_context.h"

void Audio::startup()
{
    ma_result result = ma_engine_init(nullptr, &AudioContext::instance().m_engine);
    if (result != MA_SUCCESS) {
        return;
    }

    static ma_sound sound;
    if (AudioContext::instance().load("../assets/onemoretime.mp3", sound))
    {
        AudioContext::instance().play(sound);
    }
}

void Audio::shutdown()
{
    ma_engine_uninit(&AudioContext::instance().m_engine);
}