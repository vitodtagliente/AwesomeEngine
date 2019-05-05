#include "application_null.h"

#include <cassert>
#include "../../engine/engine.h"
#include "input_null.h"
#include "time_null.h"
#include "window_null.h"

namespace awesome
{
	void ApplicationNULL::registerModules()
	{
		Engine* engine = Engine::instance();
		assert(engine != nullptr);

		engine->registerModule<Window>(new WindowNULL());
		engine->registerModule<Time>(new TimeNULL());
		engine->registerModule<Input>(new InputNULL());
	}

	void ApplicationNULL::update_implementation()
	{
	}
}