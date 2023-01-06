#include "ui.h"

#include <assert.h>


UI* UI::s_instance{ nullptr };

UI::UI()
	: ApplicationModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void UI::startup()
{

}

void UI::shutdown()
{
	
}

void UI::preRendering()
{
	
}

void UI::render()
{
	
}

void UI::postRendering()
{

}

void UI::update(const double)
{
	
}