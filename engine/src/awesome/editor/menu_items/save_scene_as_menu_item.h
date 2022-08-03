/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

namespace editor
{
	class SaveSceneAsMenuItem : public MenuItem
	{
	public:
		SaveSceneAsMenuItem() = default;
		virtual ~SaveSceneAsMenuItem() = default;

		virtual std::string getCategory() const override { return "Scene"; };
		virtual std::string getName() const override { return "Save Scene as"; };

		virtual void execute() override;

		PROTO()
	};
}