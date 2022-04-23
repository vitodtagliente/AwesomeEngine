/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/editor/menu_item.h>
#include <awesome/editor/widgets/save_file_dialog.h>

namespace editor
{
	class SpriteMenuItem : public MenuItem
	{
	public:
		SpriteMenuItem() = default;
		virtual ~SpriteMenuItem() = default;

		virtual std::string getCategory() const override { return "Assets"; };
		virtual std::string getName() const override { return "Sprite"; };

		virtual void render() override;
		virtual void execute() override;

		REFLECT()

	private:
		SaveFileDialog m_saveFileDialog;
	};
}