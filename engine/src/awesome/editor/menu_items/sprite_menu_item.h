/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/menu_item.h>

namespace editor
{
	class SpriteMenuItem : public MenuItem
	{
	public:
		SpriteMenuItem() = default;
		virtual ~SpriteMenuItem() = default;

		virtual std::string getCategory() const override { return "Assets"; };
		virtual std::string getName() const override { return "Sprite"; };

		virtual void execute() override;

		PROTO()
	};
}