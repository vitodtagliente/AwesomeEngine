#include "audio_listener_component.h"

#include <awesome/core/logger.h>

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
