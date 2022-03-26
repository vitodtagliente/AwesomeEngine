/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

namespace editor
{
	class Performance : public Window
	{
	public:
		Performance();

		void render() override;

		REFLECT()
	};
}