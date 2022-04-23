/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/editor/menu_item.h>
#include <awesome/editor/widgets/save_file_dialog.h>

namespace editor
{
	class SpriteAnimationMenuItem : public MenuItem
	{
	public:
		SpriteAnimationMenuItem() = default;
		virtual ~SpriteAnimationMenuItem() = default;

		virtual std::string getCategory() const override { return "Assets"; };
		virtual std::string getName() const override { return "Sprite Animation"; };

		virtual void render() override;
		virtual void execute() override;

		REFLECT()

	private:
		SaveFileDialog m_saveFileDialog;
	};
}