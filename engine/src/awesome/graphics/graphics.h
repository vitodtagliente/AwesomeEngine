/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application.h>

#include "context.h"
#include "renderer.h"

namespace graphics
{
	class Graphics : public Application::Module
	{
	public:
		Graphics();

		void startup() override;
		void shutdown() override;
		void preRendering() override;
		void render(graphics::Renderer* const renderer) override;
		void postRendering() override;

	private:
		Context* m_context;
		Renderer* m_renderer;
	};
}