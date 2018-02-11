#include <awesome/scenegraph/object.h>

namespace Awesome
{
	namespace Scenegraph
	{
		unsigned int Object::id_counter = 0;

		Object::Object()
		{
			id = ++id_counter;
		}

		Object::Object(std::string object_name)
		{
			id = ++id_counter;
			name = object_name;
		}

		Object::Object(std::initializer_list<Component*> init_components)
		{
			id = ++id_counter;
			for (auto it = init_components.begin(); it != init_components.end(); ++it) {
				components.push_back(*it);
			}
		}

		Object::Object(std::string object_name, std::initializer_list<Component*> init_components)
		{
			id = ++id_counter;
			name = object_name;
			for (auto it = init_components.begin(); it != init_components.end(); ++it) {
				components.push_back(*it);
			}
		}

		Component* Object::addComponent(Component* new_component)
		{
			if (new_component != nullptr)
			{
				new_component->owner_object = this;
				components.push_back(new_component);
			}
			return new_component;
		}


		bool Object::operator==(const Object& other)
		{
			return id == other.id;
		}

		void Object::init()
		{
			for (auto it = components.begin(); it != components.end(); ++it) {
				if (*it != nullptr)
					(*it)->init();
				else components.erase(it);
			}
		}

		void Object::update(float delta_time)
		{
			for (auto it = components.begin(); it != components.end(); ++it) {
				if (*it != nullptr)
					(*it)->update(delta_time);
				else components.erase(it);
			}
		}
	}
}