#include "ui.h"

#include <awesome/engine/engine.h>

#include "canvas.h"

bool UI::startup()
{
	return true;
}

void UI::shutdown()
{
}

void UI::render()
{
	
}

void UI::update(const double deltaTime)
{
	Canvas::instance().update(deltaTime);
}