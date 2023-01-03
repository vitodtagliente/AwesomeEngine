/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>

#include "weapon_component.h"

#include "shield_component_generated.h"

CLASS(Type = Component)
class ShieldComponent : public graphics::IGraphicsComponent, public WeaponComponent
{
public:
	ShieldComponent() = default;
	virtual ~ShieldComponent() = default;

	virtual void init() override;
	virtual void render(class graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	double m_activationTimer{ 0 };
	PROPERTY() graphics::Color m_color{ graphics::Color::Yellow };

	void activate();
};