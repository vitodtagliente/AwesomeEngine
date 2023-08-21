/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "color.h"

namespace graphics
{
	class RenderTarget
	{
	public:
		enum class State
		{
			Unknown,
			Error,
			Initialized
		};

		RenderTarget(int width, int height, const Color& color = Color::White);
		~RenderTarget();

		void resize(int width, int height);

		inline unsigned int width() const { return m_width; }
		inline unsigned int height() const { return m_height; }

		void free();

		// clear color
		graphics::Color color;

	private:
		// framebuffer size
		int m_width, m_height;
		// the error message
		std::string m_errorMessage;
		// The state
		State m_state{ State::Unknown };
	};
}