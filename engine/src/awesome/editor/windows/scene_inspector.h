/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "../window.h"

class Entity;

namespace editor
{
	class Context;

	class SceneInspector : public Window
	{
	public:
		SceneInspector();

		std::string getTitle() const override;
		void render(Context& context) override;
	};
}