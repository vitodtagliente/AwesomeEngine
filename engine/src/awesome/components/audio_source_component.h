/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/audio_asset.h>
#include <awesome/scene/component.h>

#include "audio_source_component_generated.h"

CLASS(Type = Component, Category = Audio)
class AudioSourceComponent : public Component
{
public:	
	enum class State
	{
		Paused,
		Playing, 
		Stopped
	};

	friend class AudioSourceComponentInspector;

	void init() override;

	void pause();
	void play();
	void resume();
	void stop();

	State state() const { return m_state; }

	void apply();

	PROPERTY() AudioAsset audio;
	PROPERTY() bool loop{ false };
	PROPERTY() float pitch{ 1.0f };
	PROPERTY() float volume{ 1.0f };

	GENERATED_BODY()

private:
	PROPERTY() bool m_playOnAwake{ false };
	State m_state{ State::Stopped };
};