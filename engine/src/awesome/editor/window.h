/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

namespace editor
{
	class Context;

	class Window
	{
	public:
		Window();

		virtual std::string getTitle() const;
		virtual void render(Context& context) {}
	};
}