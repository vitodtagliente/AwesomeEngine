/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

#include "show_windows_menu_item_generated.h"

CLASS()
class ShowWindowsMenuItem : public MenuItem
{
public:
	ShowWindowsMenuItem() = default;
	virtual ~ShowWindowsMenuItem() = default;

	virtual std::string getCategory() const override { return "View"; };
	virtual std::string getName() const override;

	virtual void execute() override;

	GENERATED_BODY()
};