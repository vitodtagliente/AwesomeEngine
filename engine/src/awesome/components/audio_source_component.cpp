#include "audio_source_component.h"

#include <miniaudio.h>

#include <awesome/engine/engine.h>
#include <awesome/graphics/renderer.h>

AudioSourceComponent::AudioSourceComponent()
	: Component()
	, m_renderSettings(Engine::instance().settings.renderer)
{
}

void AudioSourceComponent::init()
{
	if (!audio.ready()) return;

	m_stream = AudioEngine::instance()->stream(audio);
	m_pendingPlay = m_playOnAwake && m_stream;
}

void AudioSourceComponent::render(graphics::Renderer& renderer)
{
	if (m_renderSettings.debug && m_renderSettings.renderAudioSources)
	{
		const math::vec3& position = getOwnerTransform().position;
		renderer.submitDrawCircle(graphics::ShapeRenderStyle::stroke, math::vec3(position.x, position.y, 0.f), minDistance, m_renderSettings.audioSourceWireColor);
		auto max_distance_color = m_renderSettings.audioSourceWireColor;
		max_distance_color.alpha = 0.5f;
		renderer.submitDrawCircle(graphics::ShapeRenderStyle::stroke, math::vec3(position.x, position.y, 0.f), maxDistance, max_distance_color);
	}
}

void AudioSourceComponent::update(double)
{
	if (m_pendingPlay)
	{
		apply();
		m_stream->play();
		m_pendingPlay = false;
	}
}

void AudioSourceComponent::apply()
{
	if (m_stream)
	{
		m_stream->setLooping(loop);
		m_stream->setPitch(pitch);
		m_stream->setVolume(volume);

		ma_sound_set_spatialization_enabled(m_stream->data(), true);
		switch (rolloffMode)
		{
		case AudioRolloffMode::Exponential:ma_sound_set_attenuation_model(m_stream->data(), ma_attenuation_model_exponential); break;
		case AudioRolloffMode::Inverse:ma_sound_set_attenuation_model(m_stream->data(), ma_attenuation_model_inverse); break;
		case AudioRolloffMode::Linear:ma_sound_set_attenuation_model(m_stream->data(), ma_attenuation_model_linear); break;
		case AudioRolloffMode::None:
		default:ma_sound_set_attenuation_model(m_stream->data(), ma_attenuation_model_none); break;
		}
		ma_sound_set_rolloff(m_stream->data(), rolloff);
		ma_sound_set_min_gain(m_stream->data(), minGain);
		ma_sound_set_max_gain(m_stream->data(), maxGain);
		ma_sound_set_min_distance(m_stream->data(), minDistance);
		ma_sound_set_max_distance(m_stream->data(), maxDistance);
	}
}