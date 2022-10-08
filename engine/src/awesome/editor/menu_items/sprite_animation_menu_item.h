/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

#include "sprite_animation_menu_item_generated.h"

CLASS(Category = MenuItem)
	class SpriteAnimationMenuItem : public MenuItem
	{
	public:
		SpriteAnimationMenuItem() = default;
		virtual ~SpriteAnimationMenuItem() = default;

		virtual std::string getCategory() const override { return "Assets"; };
		virtual std::string getName() const override { return "Sprite Animation"; };

		virtual void execute() override;

		GENERATED_BODY()
	};