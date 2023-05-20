#include "audio_stream.h"

#include <algorithm>
#include <miniaudio.h>

AudioStream::AudioStream(const AudioAsset& asset)
{
	m_data = new ma_sound();
	m_id = asset.id;
	m_path = asset.path;
}

AudioStream::~AudioStream()
{
	stop();
	delete m_data;
}

void AudioStream::pause()
{
	m_state = ma_sound_stop(m_data) == MA_SUCCESS
		? State::Paused
		: State::Stopped;
}

void AudioStream::play()
{
	ma_sound_seek_to_pcm_frame(m_data, 0);
	m_state = ma_sound_start(m_data) == MA_SUCCESS
		? State::Playing
		: State::Stopped;
}

void AudioStream::resume()
{
	m_state = ma_sound_start(m_data) == MA_SUCCESS
		? State::Playing
		: State::Stopped;
}

void AudioStream::stop()
{
	ma_sound_stop(m_data);
	ma_sound_seek_to_pcm_frame(m_data, 0);
	m_state = State::Stopped;
}

void AudioStream::setLooping(const bool value)
{
	ma_sound_set_looping(m_data, static_cast<ma_bool32>(value));
}

void AudioStream::setPitch(const float value)
{
	ma_sound_set_pitch(m_data, std::clamp(value, 0.f, 1.f));
}

void AudioStream::setVolume(const float value)
{
	ma_sound_set_volume(m_data, std::clamp(value, 0.f, 1.f));
}