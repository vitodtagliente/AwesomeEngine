/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <memory>

#include "canvas.h"

class Application
{
public:

	Application();
	virtual ~Application();

	int run();

	inline const Canvas& getCanvas() const { return m_canvas; }

private:

	void update();
	void render();

	Canvas m_canvas;
};