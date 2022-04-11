/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/application/application.h>

#include "state.h"
#include "window.h"

namespace graphics
{
	class Renderer;
}

namespace editor
{
	class Editor : public Application::Module
	{
	public:
		Editor() = default;

		virtual void startup() override;
		virtual void shutdown() override;
		virtual void preRendering() override;
		virtual void render(graphics::Renderer* const renderer) override;
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
	};
}