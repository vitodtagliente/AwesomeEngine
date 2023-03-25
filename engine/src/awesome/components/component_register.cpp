#include "component_register.h"

#include <awesome/core/reflection.h>
#include "component_library.h"

void ComponentRegister::execute()
{
	ComponentLibrary& library = ComponentLibrary::instance();
	for (const auto& [name, options] : TypeFactory::list("Type", "Component"))
	{
		std::string category;
		const meta_t& meta = std::get<0>(options);
		const auto& it = meta.find("Category");
		if (it != meta.end())
		{
			category = it->second;
		}
		library.push_back({ name, category });
	}
}