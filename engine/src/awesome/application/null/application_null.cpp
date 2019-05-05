#include "application_null.h"

#include <cassert>
#include "../../engine/engine.h"
#include "input_null.h"
#include "time_null.h"
#include "window_null.h"

namespace awesome
{
	void ApplicationNULL::registerModules(Engine* const t_engine)
	{
		t_engine->registerModule<Window>(new WindowNULL());
		t_engine->registerModule<Time>(new TimeNULL());
		t_engine->registerModule<Input>(new InputNULL());
	}
}