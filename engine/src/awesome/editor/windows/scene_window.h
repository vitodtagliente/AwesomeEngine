/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/editor/window.h>

namespace editor
{
	class SceneWindow : public Window
	{
	public:
		SceneWindow() = default;

		std::string getTitle() const override;
		void render() override;

		REFLECT()

	private:
		std::string m_filename;
	};
}