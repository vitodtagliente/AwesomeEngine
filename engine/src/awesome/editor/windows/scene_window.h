/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/uuid.h>
#include <awesome/editor/widgets/select_list.h>
#include <awesome/editor/window.h>

namespace editor
{
	class SceneWindow : public Window
	{
	public:
		SceneWindow();

		std::string getTitle() const override { return "Scene"; }
		void render() override;

		REFLECT()

	private:
		SelectList<uuid> m_list;
	};
}