#include <awesome/component.h>

namespace Awesome
{
	Component::Component()
	{
		
	}

	Component::~Component()
	{

	}

	bool Component::operator== (const Component& other)
	{
		return id == other.id;
	}
}