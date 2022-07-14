/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

namespace editor
{
	class SaveSceneMenuItem : public MenuItem
	{
	public:
		SaveSceneMenuItem() = default;
		virtual ~SaveSceneMenuItem() = default;

		virtual std::string getCategory() const override { return "Scene"; };
		virtual std::string getName() const override { return "Save Scene"; };

		virtual void execute() override;

		REFLECT()
	};
}