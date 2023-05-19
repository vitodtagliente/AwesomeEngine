#include "audio_source_component_inspector.h"

#include <awesome/components/audio_source_component.h>
#include <awesome/editor/editor_ui.h>

bool AudioSourceComponentInspector::canInspect(Component& component) const
{
	return component.type_name() == reflect::Type<AudioSourceComponent>::name();
}

void AudioSourceComponentInspector::inspect(Component& component)
{
	AudioSourceComponent& audio_source = dynamic_cast<AudioSourceComponent&>(component);
	EditorUI::input("enabled", audio_source.enabled);

	EditorUI::input("Audio", audio_source.audio);
	EditorUI::input("Play On Awake", audio_source.m_playOnAwake);

	bool apply = false;
	
	bool previousLoop = audio_source.loop;
	EditorUI::input("Loop", audio_source.loop);
	apply |= (previousLoop != audio_source.loop);

	float previousPitch = audio_source.pitch;
	EditorUI::slider("Pitch", 0.f, 1.f, audio_source.pitch);
	apply |= (previousPitch != audio_source.pitch);

	float previousVolume = audio_source.volume;
	EditorUI::slider("Volume", 0.f, 1.f, audio_source.volume);
	apply |= (previousVolume != audio_source.volume);

	if (apply)
	{
		audio_source.apply();
	}

	EditorUI::separatorText("Player");

	switch (audio_source.state())
	{
	case AudioSourceComponent::State::Stopped:
	{
		if (EditorUI::button(EditorUI::Icon::play.c_str()))
		{
			audio_source.play();
		}
		break;
	}
	case AudioSourceComponent::State::Paused:
	{
		if (EditorUI::button(EditorUI::Icon::play.c_str()))
		{
			audio_source.resume();
		}
		EditorUI::sameLine();
		if (EditorUI::button(EditorUI::Icon::stop.c_str()))
		{
			audio_source.stop();
		}
		break;
	}
	case AudioSourceComponent::State::Playing:
	default:
	{
		if (EditorUI::button(EditorUI::Icon::pause.c_str()))
		{
			audio_source.pause();
		}
		EditorUI::sameLine();
		if (EditorUI::button(EditorUI::Icon::stop.c_str()))
		{
			audio_source.stop();
		}
		break;
	}
	}
}