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

		virtual void startup() override;
		virtual void shutdown() override;
		virtual void preRendering() override;
		virtual void postRendering() override;
	};
}