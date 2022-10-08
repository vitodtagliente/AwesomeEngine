/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

#include "new_scene_menu_item_generated.h"

CLASS(Category = MenuItem)
class NewSceneMenuItem : public MenuItem
{
public:
	NewSceneMenuItem() = default;
	virtual ~NewSceneMenuItem() = default;

	virtual std::string getCategory() const override { return "Scene"; };
	virtual std::string getName() const override { return "New Scene..."; };

	virtual void execute() override;

	GENERATED_BODY()
};