/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/singleton.h>

#include "../window.h"

namespace editor
{
	class Context;

	class Performance : public Window
	{
	public:
		Performance();

		std::string getTitle() const override;
		void render(Context& context) override;
	};
}