#include "ui.h"

#include <awesome/engine/engine.h>

UI::UI()
	: m_canvas(UIGraph::instance())
{
}

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
	m_canvas.update(deltaTime);
}