/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application.h>

#include "context.h"

namespace graphics
{
	class Renderer;
}

namespace editor
{
	class Window;

	class Editor : public Application::Module
	{
	public:
		Editor();

		void startup() override;
		void shutdown() override;
		void preRendering() override;
		void render(graphics::Renderer& renderer) override;
		void postRendering() override;

	private:
		Context m_context;
		std::vector<Window*> m_windows;
	};
}