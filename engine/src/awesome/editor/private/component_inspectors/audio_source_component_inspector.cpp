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

	EditorUI::separatorText("Spatialization");

	AudioRolloffMode previousRolloffMode = audio_source.rolloffMode;
	EditorUI::input("Rolloff Mode", audio_source.rolloffMode);
	apply |= (previousRolloffMode != audio_source.rolloffMode);

	float previousRolloff = audio_source.rolloff;
	EditorUI::slider("Rolloff", 0.f, 1.f, audio_source.rolloff);
	apply |= (previousRolloff != audio_source.rolloff);

	float previousMinDistance = audio_source.minDistance;
	EditorUI::input("Min Distance", audio_source.minDistance);
	apply |= (previousMinDistance != audio_source.minDistance);

	float previousMaxDistance = audio_source.maxDistance;
	EditorUI::input("Max Distance", audio_source.maxDistance);
	apply |= (previousMaxDistance != audio_source.maxDistance);

	float previousMinGain = audio_source.minGain;
	EditorUI::slider("Min Gain", 0.f, 1.f, audio_source.minGain);
	apply |= (previousMinGain != audio_source.minGain);

	float previousMaxGain = audio_source.maxGain;
	EditorUI::slider("Max Gain", 0.f, 1.f, audio_source.maxGain);
	apply |= (previousMaxGain != audio_source.maxGain);

	if (apply)
	{
		audio_source.apply();
	}

	EditorUI::Audio::player(audio_source.stream());
}