/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/application/application.h>

#include "context.h"
#include "selection_system.h"

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

		virtual void startup() override;
		virtual void shutdown() override;
		virtual void preRendering() override;
		virtual void render(graphics::Renderer* const renderer) override;
		virtual void postRendering() override;
		virtual void update(double deltaTime) override;

		template <typename T = Window>
		T* const addWindow()
		{
			T* const window = new T();
			m_windows.push_back(window);
			return window;
		}

	private:
		void registerWindows();

		Context m_context;
		SelectionSystem m_selectionSystem;
		std::vector<Window*> m_windows;
	};
}