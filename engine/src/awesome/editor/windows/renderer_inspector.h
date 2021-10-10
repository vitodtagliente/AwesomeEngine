/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "../window.h"

class Entity;

namespace editor
{
	class Context;

	class RendererInspector : public Window
	{
	public:
		RendererInspector();

		std::string getTitle() const override;
		void render(Context& context) override;
	};
}