/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <memory>

#include "canvas.h"
#include <awesome/scene/world.h>

class Application
{
public:

	Application();
	virtual ~Application();

	int run();

	inline const Canvas& getCanvas() const { return m_canvas; }
	inline Canvas& getCanvas() { return m_canvas; }
	inline const World& getWorld() const { return m_world; }
	inline World& getWorld() { return m_world; }

private:

	void update();
	void render();

	Canvas m_canvas;
	World m_world;
};