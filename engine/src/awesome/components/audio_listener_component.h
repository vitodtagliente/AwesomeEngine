/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>

#include "audio_listener_component_generated.h"

CLASS(Type = Component, Category = Audio)
class AudioListenerComponent : public Component
{
public:	
	void init() override;
	void uninit() override;
	void update(double deltaTime) override;

	static AudioListenerComponent* const instance() { return s_instance; }

	GENERATED_BODY()

private:
	static inline AudioListenerComponent* s_instance{ nullptr };
};