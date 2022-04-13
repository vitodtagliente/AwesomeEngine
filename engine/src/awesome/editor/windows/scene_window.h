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

		std::string getTitle() const override { return "Scene"; }
		void update(double deltaTime) override;
		void render() override;

		REFLECT()

	private:
		std::string m_filename;
		bool m_renaming;
	};
}