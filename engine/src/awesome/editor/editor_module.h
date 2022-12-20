/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/application/application.h>
#include <awesome/component/components.h>
#include <awesome/editor/state.h>

#include "private/menu.h"
#include "window.h"

namespace graphics
{
	class Renderer2D;
}

namespace editor
{
	class Module : public Application::Module
	{
	public:
		Module() = default;

		virtual void startup() override;
		virtual void shutdown() override;
		virtual void preRendering() override;
		virtual void render(graphics::Renderer2D* const renderer) override;
		virtual void postRendering() override;
		virtual void update(double deltaTime) override;

		template <typename T = Window>
		void registerWindow()
		{
			m_windows.push_back(std::make_unique<T>());
		}

	private:
		void registerWindows();

		State m_state;
		std::vector<std::unique_ptr<Window>> m_windows;
		Menu m_menu;
	};
}