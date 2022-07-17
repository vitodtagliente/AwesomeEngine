/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/singleton.h>
#include "renderer.h"

namespace graphics
{
	class Context : public Singleton<Context>
	{
	public:
		friend class Module;

		Context();

		Renderer2D renderer;
		inline int getDrawCalls() const { return m_drawCalls; }

	private:
		int m_drawCalls;
	};
}