/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

namespace editor
{
	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual std::string getTitle() const = 0;
		inline bool hasFocus() const { return m_hasFocus; }

		void setFocus(bool focus);

		virtual void init() {}
		virtual void render() {}
		virtual void update(double /*deltaTime*/) {}

		virtual void onFocusChange(bool /*focus*/) {}

	private:
		bool m_hasFocus{ false };
	};	
}