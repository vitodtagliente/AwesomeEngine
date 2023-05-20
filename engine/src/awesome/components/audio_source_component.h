/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/audio_asset.h>
#include <awesome/audio/audio_engine.h>
#include <awesome/scene/component.h>

#include "audio_source_component_generated.h"

CLASS(Type = Component, Category = Audio)
class AudioSourceComponent : public Component
{
public:	
	friend class AudioSourceComponentInspector;

	void init() override;

	void apply();

	PROPERTY() AudioAsset audio;
	PROPERTY() bool loop{ false };
	PROPERTY() float pitch{ 1.0f };
	PROPERTY() float volume{ 1.0f };

	AudioStreamPtr stream() const { return m_stream; }

	GENERATED_BODY()

private:
	PROPERTY() bool m_playOnAwake{ false };
	AudioStreamPtr m_stream{ nullptr };
};