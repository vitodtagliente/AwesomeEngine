/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "../window.h"

namespace editor
{
	class Context;

	class EntityInspector : public Window
	{
	public:
		EntityInspector();

		std::string getTitle() const override;
		void render(Context& context) override;
	};
}