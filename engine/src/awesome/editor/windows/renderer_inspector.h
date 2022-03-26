/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>
#include <awesome/graphics/renderer.h>

namespace editor
{
	class RendererInspector : public Window
	{
	public:
		RendererInspector();

		std::string getTitle() const override;
		virtual void render() override;
		virtual void update(double deltaTime) override;

		REFLECT()

	private:
		graphics::Renderer::Stats m_stats;
	};
}