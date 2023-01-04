/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_asset.h>
#include <awesome/core/timer.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/ui/ui_component.h>

#include "button_component_generated.h"

CLASS(Type = Component, Category = UI)
class ButtonComponent : public IUIComponent, public Component
{
public:
	ButtonComponent() = default;
	virtual ~ButtonComponent() = default;

	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	PROPERTY() graphics::Color m_clickColor{ graphics::Color::White };
	PROPERTY() double m_clickDuration{ .1 };
	Timer m_clickTimer{ .1 };
	bool m_isHovered{ false };
	PROPERTY() graphics::Color m_normalColor{ graphics::Color::White };
	PROPERTY() graphics::Color m_hoveredColor{ graphics::Color::White };
	PROPERTY() SpriteAssetPtr m_sprite;
};