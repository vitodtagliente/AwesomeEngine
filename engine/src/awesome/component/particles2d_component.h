/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/particle_system.h>

#include "particles2d_component_generated.h"

namespace graphics
{
	class Renderer2D;
}

CLASS(Type = Component)
class Particles2dComponent : public Component
{
public:
	Particles2dComponent() = default;
	virtual ~Particles2dComponent() = default;

	virtual void init() override;
	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	void play();
	void pause();
	void resume();
	void stop();

	bool isPlaying() const;

	PROPERTY() bool autoplay{ false };
	PROPERTY() bool loop{ false };

	GENERATED_BODY()

private:
	graphics::ParticleSystem m_system;
};