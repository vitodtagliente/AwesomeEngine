#include "audio.h"

#include <assert.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include "audio_context.h"

Audio* Audio::s_instance{ nullptr };

Audio::Audio()
    : ApplicationModule()
{
    assert(s_instance == nullptr);
    s_instance = this;
}

void Audio::startup()
{
    ma_result result = ma_engine_init(nullptr, &AudioContext::instance().m_engine);
    if (result != MA_SUCCESS) {
        return;
    }
}

void Audio::shutdown()
{
    ma_engine_uninit(&AudioContext::instance().m_engine);
}