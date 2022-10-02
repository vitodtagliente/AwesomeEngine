/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

#include "sprite_menu_item_generated.h"

CLASS()
class SpriteMenuItem : public MenuItem
{
public:
	SpriteMenuItem() = default;
	virtual ~SpriteMenuItem() = default;

	virtual std::string getCategory() const override { return "Assets"; };
	virtual std::string getName() const override { return "Sprite"; };

	virtual void execute() override;

	GENERATED_BODY()
};