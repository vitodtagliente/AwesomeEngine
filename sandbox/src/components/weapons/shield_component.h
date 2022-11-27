/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>

#include "weapon_component.h"

#include "shield_component_generated.h"

CLASS(Category = Component)
class ShiedComponent : public graphics::IGraphicsComponent, public WeaponComponent
{
public:
	ShiedComponent() = default;
	virtual ~ShiedComponent() = default;

	virtual void init() override;
	virtual void render(class graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	PROPERTY() int power{ 1 };
	PROPERTY() double frequency{ 1 };
	PROPERTY() float range{ 1.f };

	GENERATED_BODY()

private:
	double m_activationTimer{ 0 };
	PROPERTY() graphics::Color m_color{ graphics::Color::Yellow };

	void activate();
};