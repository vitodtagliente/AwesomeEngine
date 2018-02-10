#include <awesome/scenegraph/component.h>
#include <awesome/scenegraph/object.h>

namespace Awesome
{
	namespace Scenegraph
	{
		unsigned int Component::id_counter = 0;

		Component::Component()
		{
			id = ++id_counter;
		}

		Component::Component(Object* component_owner)
		{
			id = ++id_counter;
			owner = component_owner;
		}
	}
}