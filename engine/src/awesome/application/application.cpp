#include "application.h"

#include <cassert>
#include "input.h"
#include "time.h"
#include "window.h"
#include "../engine/module.h"

namespace awesome
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	bool Application::startup_imp()
	{
		return true;
	}
}