/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/graphics/particle_system.h>

#include "particles2d_component_generated.h"

CLASS(Type = Component)
class Particles2dComponent : public graphics::IGraphicsComponent, public Component
{
public:
	Particles2dComponent() = default;
	virtual ~Particles2dComponent() = default;

	virtual void init() override;
	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

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