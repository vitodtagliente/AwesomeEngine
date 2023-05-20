#include "audio_source_component.h"

void AudioSourceComponent::init()
{
	if (!audio.ready()) return;

	m_stream = AudioEngine::instance()->stream(audio);

	if (m_playOnAwake && m_stream)
	{
		apply();
		m_stream->play();
	}
}


void AudioSourceComponent::apply()
{
	if (m_stream)
	{
		m_stream->setLooping(loop);
		m_stream->setPitch(pitch);
		m_stream->setVolume(volume);
	}	
}