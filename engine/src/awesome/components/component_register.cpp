#include "component_register.h"
#include "component_library.h"
#include "rigidbody2d_component.h"

#include <awesome/core/reflection.h>
#include <awesome/ecs/entities_coordinator.h>



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
	EntitiesCoordinator::instance().RegisterComponent<Rigidbody2DComponent>();
}