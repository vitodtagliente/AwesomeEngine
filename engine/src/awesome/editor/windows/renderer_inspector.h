/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

namespace editor
{
	class RendererInspector : public Window
	{
	public:
		RendererInspector();

		std::string getTitle() const override;
		void render() override;

		REFLECT()
	};
}