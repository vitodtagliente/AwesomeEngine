/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "panel.h"

namespace graphics
{
	class Renderer;
}

class RendererInspector
{
public:
	RendererInspector();

	void render(graphics::Renderer& renderer);

};