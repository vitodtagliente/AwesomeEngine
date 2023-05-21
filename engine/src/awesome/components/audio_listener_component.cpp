#include "audio_listener_component.h"

#include <awesome/core/logger.h>

#include <miniaudio.h>

extern ma_engine* audio_context;

void AudioListenerComponent::init()
{
	if (s_instance != nullptr)
	{
		WARN_LOG(type_name(), "Found another valid instance of this component");
	}
	s_instance = this;
}

void AudioListenerComponent::uninit()
{
	s_instance = nullptr;
}

void AudioListenerComponent::update(const double)
{
	static constexpr int local_listener_index = 0;
	const math::vec3& position = getOwnerTransform().position;
	ma_engine_listener_set_position(audio_context, local_listener_index, position.x, position.y, position.z);
}