#include "component.h"

namespace awesome
{
	Component::Component()
		: name()
		, enabled(true)
		, m_id()
		, m_owner()
	{
	}
	
	Component::~Component()
	{
	}
}