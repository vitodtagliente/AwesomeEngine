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
		Context();

		Renderer2D renderer;		
	};
}