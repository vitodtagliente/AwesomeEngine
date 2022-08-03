/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

namespace editor
{
	class ShowWindowsMenuItem : public MenuItem
	{
	public:
		ShowWindowsMenuItem() = default;
		virtual ~ShowWindowsMenuItem() = default;

		virtual std::string getCategory() const override { return "View"; };
		virtual std::string getName() const override;

		virtual void execute() override;

		PROTO()
	};
}