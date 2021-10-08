/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <memory>

#include "canvas.h"
#include "input.h"
#include <awesome/scene/world.h>
#include <awesome/core/time.h>

class Application
{
public:

	Application();
	virtual ~Application();

	int run();

	inline const Canvas& getCanvas() const { return m_canvas; }
	inline Canvas& getCanvas() { return m_canvas; }
	inline const Input& getInput() const { return m_input; }
	inline Input& getInput() { return m_input; }
	inline const World& getWorld() const { return m_world; }
	inline World& getWorld() { return m_world; }

private:

	void update();
	void render();

	Canvas m_canvas;
	Input m_input;
	Time m_time;
	World m_world;
};