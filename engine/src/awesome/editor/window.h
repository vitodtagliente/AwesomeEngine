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
		Window();

		virtual std::string getTitle() const;

		virtual void init();
		virtual void update(double deltaTime);
		virtual void render();

		REFLECT()

	protected:

		State* const getState() const { return State::instance(); }

	private:
		State* m_state;
	};
}