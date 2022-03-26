/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

namespace editor
{
	class SceneInspector : public Window
	{
	public:
		SceneInspector();

		std::string getTitle() const override;
		void render() override;

		REFLECT()
	};
}