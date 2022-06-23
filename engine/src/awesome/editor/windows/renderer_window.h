/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>
#include <awesome/graphics/renderer.h>

namespace editor
{
	class RendererWindow : public Window
	{
	public:
		RendererWindow() = default;

		std::string getTitle() const override { return "Renderer"; }
		virtual void render() override;
		virtual void update(double deltaTime) override;

		REFLECT()
	};
}