#include <awesome/scenegraph/object.h>
#include <awesome/scenegraph/component.h>

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
			for (auto begin = init_components.begin(); begin != init_components.end(); ++begin) {
				components.push_back(*begin);
			}
		}

		Object::Object(std::string object_name, std::initializer_list<Component*> init_components)
		{
			id = ++id_counter;
			name = object_name;
			for (auto begin = init_components.begin(); begin != init_components.end(); ++begin) {
				components.push_back(*begin);
			}
		}

		bool Object::operator==(const Object& other)
		{
			return id == other.id;
		}

		void Object::init()
		{

		}

		void Object::update(float delta_time)
		{

		}
	}
}