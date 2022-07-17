/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/graphics/particle_system.h>

namespace graphics
{
	class Renderer2D;
}

namespace component
{
	class Particles2d : public Component, public graphics::IGraphicsComponent
	{
	public:
		Particles2d() = default;
		virtual ~Particles2d() = default;

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

		bool autoplay{ false };
		bool loop{ false };

		REFLECT()

	private:
		graphics::ParticleSystem m_system;
	};
}