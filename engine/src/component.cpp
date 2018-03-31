#include <awesome/component.h>

namespace Awesome
{
	Component::Component()
	{
		
	}

	Component::~Component()
	{

	}

	void Component::init()
	{

	}

	void Component::update(float delta_time)
	{

	}

	void Component::free()
	{

	}

	bool Component::operator== (const Component& other)
	{
		return id == other.id;
	}
}