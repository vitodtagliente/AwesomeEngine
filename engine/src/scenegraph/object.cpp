#include <awesome/scenegraph/object.h>

namespace Awesome
{
	namespace Scenegraph
	{
		bool Object::operator==(const Object& other)
		{
			return id == other.id;
		}

		template <class T>
		std::vector<Component*> Object::findComponents()
		{
			std::vector<Component*> found_components;
			for (auto it = myvector.begin(); it != components.end(); ++it)
			{
				if (typeof(*it) == typeof(T))
					found_components.push_back(*it);
			}
			return found_components;
		}

		template <class T>
		Component* Object::findComponent()
		{
			for (auto it = myvector.begin(); it != components.end(); ++it)
			{
				if (typeof(*it) == typeof(T))
					return *it;
			}
			return nullptr;
		}
	}
}