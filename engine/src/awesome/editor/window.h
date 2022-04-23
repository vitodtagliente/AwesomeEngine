/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>

namespace editor
{
	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual std::string getTitle() const;
		inline bool hasFocus() const { return m_hasFocus; }

		void setFocus(bool focus);

		virtual void init() {}
		virtual void render() {}
		virtual void update(double /*deltaTime*/) {}

		virtual void onFocusChange(bool /*focus*/) {}

		REFLECT()

	private:
		bool m_hasFocus{ false };
	};

#define REFLECT_WINDOW(T) REFLECT_IMP_CATEGORY(T, Window)
}