/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>
#include <awesome/editor/state.h>

namespace editor
{
	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual std::string getTitle() const;

		virtual void init() {}
		virtual void update(double /*deltatime*/) {}
		virtual void render() {}

		REFLECT()

	protected:

		State* const getState() const { return &State::instance(); }
	};

#define REFLECT_WINDOW(T) REFLECT_IMP_CATEGORY(T, Window)
}