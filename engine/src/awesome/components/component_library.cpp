#include "component_library.h"

#include <awesome/core/reflection.h>

ComponentRecord::ComponentRecord(const std::string& name, const std::string& category)
	: name(name)
	, category(category)
{
}

Component* const ComponentRecord::instantiate() const
{
	return TypeFactory::instantiate<Component>(name);
}

const ComponentRecord* const ComponentLibrary::find(const std::string& name) const
{
	const auto& it = std::find_if(
		m_records.begin(),
		m_records.end(),
		[&name](const ComponentRecord& record) -> bool
		{
			return record.name == name;
		}
	);

	if (it != m_records.end())
	{
		return &(*it);
	}
	return nullptr;
}

void ComponentLibrary::push_back(const ComponentRecord& record)
{
	m_records.push_back(record);
}