/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

#include "tileset_menu_item_generated.h"

CLASS(Category = MenuItem)
class TilesetMenuItem : public MenuItem
{
public:
	TilesetMenuItem() = default;
	virtual ~TilesetMenuItem() = default;

	virtual std::string getCategory() const override { return "Assets"; };
	virtual std::string getName() const override { return "Tileset"; };

	virtual void execute() override;

	GENERATED_BODY()
};