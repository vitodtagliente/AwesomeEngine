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

		bool Component::operator== (const Component& other)
		{
			return id == other.id;
		}
	}
}