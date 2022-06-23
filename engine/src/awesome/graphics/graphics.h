/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application.h>

namespace graphics
{
	class Graphics : public Application::Module
	{
	public:
		Graphics() = default;

		void startup() override;
		void shutdown() override;
		void preRendering() override;
		void postRendering() override;
	};
}