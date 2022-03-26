/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/application/application.h>

#include "state.h"

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
		void const registerWindow()
		{
			T* const window = new T();
			m_windows.push_back(std::unique_ptr<Window>(window));
		}

	private:
		void registerWindows();

		State m_state;
		std::vector<std::unique_ptr<Window>> m_windows;
	};
}