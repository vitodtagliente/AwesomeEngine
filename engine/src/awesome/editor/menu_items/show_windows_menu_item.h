/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <vdtproto/runtime.h>

#include <awesome/editor/menu_item.h>

namespace editor
{
	class ShowWindowsMenuItem : public MenuItem, public IProtoClass
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