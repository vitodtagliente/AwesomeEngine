#include "audio_source_component.h"

#include <miniaudio.h>

void AudioSourceComponent::init()
{
	apply();
	if (m_playOnAwake)
	{
		play();
	}
}

void AudioSourceComponent::pause()
{
	if (!audio.ready()) return;

	Audio* sound = audio.resource.get();
	m_state = ma_sound_stop(sound) == MA_SUCCESS
		? State::Paused
		: State::Stopped;
}

void AudioSourceComponent::play()
{
	if (!audio.ready()) return;

	Audio* sound = audio.resource.get();
	ma_sound_seek_to_pcm_frame(sound, 0);
	m_state = ma_sound_start(sound) == MA_SUCCESS 
		? State::Playing
		: State::Stopped;	
}

void AudioSourceComponent::resume()
{
	if (!audio.ready()) return;

	Audio* sound = audio.resource.get(); 
	m_state = ma_sound_start(sound) == MA_SUCCESS
		? State::Playing
		: State::Stopped;
}

void AudioSourceComponent::stop()
{
	if (!audio.ready()) return;

	Audio* sound = audio.resource.get();
	ma_sound_stop(sound);
	ma_sound_seek_to_pcm_frame(sound, 0);
	m_state = State::Stopped;
}

void AudioSourceComponent::apply()
{
	if (!audio.ready()) return;

	Audio* sound = audio.resource.get();
	ma_sound_set_looping(sound, static_cast<ma_bool32>(loop));
	ma_sound_set_pitch(sound, pitch);
	ma_sound_set_volume(sound, volume);
}