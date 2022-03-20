/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>

namespace editor
{
	class Context;

	class Window
	{
	public:
		Window();

		virtual std::string getTitle() const;
		virtual void render(Context&);

		REFLECT()
	};
}