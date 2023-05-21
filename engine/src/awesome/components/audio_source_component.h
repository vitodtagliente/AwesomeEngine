/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/audio_asset.h>
#include <awesome/audio/audio_engine.h>
#include <awesome/engine/engine_settings.h>
#include <awesome/scene/component.h>

#include "audio_source_component_generated.h"

namespace graphics
{
	class Renderer;
}

ENUM()
enum class AudioRolloffMode : int
{
	None = 0,
	Inverse,
	Linear,
	Exponential
};

CLASS(Type = Component, Category = Audio)
class AudioSourceComponent : public Component
{
public:	
	friend class AudioSourceComponentInspector;

	AudioSourceComponent();
	void init() override;
	void render(graphics::Renderer& renderer) override;
	void update(double /*deltaTime*/) override;

	void apply();

	PROPERTY() AudioAsset audio;
	PROPERTY() bool loop{ false };
	PROPERTY() float pitch{ 1.0f };
	PROPERTY() float volume{ 1.0f };

	PROPERTY() float maxDistance{ 10.f };
	PROPERTY() float maxGain{ 1.f };
	PROPERTY() float minDistance{ 1.f };
	PROPERTY() float minGain{ 1.f };
	PROPERTY() float rolloff{ 1.f };
	PROPERTY() AudioRolloffMode rolloffMode { AudioRolloffMode::Linear };
	PROPERTY() bool useSpatialization{ true };

	AudioStreamPtr stream() const { return m_stream; }

	GENERATED_BODY()

private:
	bool m_pendingPlay{ false };
	PROPERTY() bool m_playOnAwake{ false };
	const RendererSettings& m_renderSettings;
	AudioStreamPtr m_stream{ nullptr };
};