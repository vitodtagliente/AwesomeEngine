#include <awesome/scenegraph/scene.h>
#include <awesome/scenegraph/object.h>
#include <cassert>

namespace Awesome
{
	namespace Scenegraph
	{
		Scene::Scene()
		{

		}

		template <class T>
		Object* Scene::spawn(std::string name)
		{
			assert(typeof(Object) == typeof(T));
			T* t_object = new T{};
			Object* new_object = ((Object*)t_object);
			new_object->name = name;
			objects.push_back(new_object);
			return new_object;
		}

		template <class T>
		Object* Scene::spawn(std::string name, Object* parent)
		{
			assert(typeof(Object) == typeof(T));
			T* t_object = new T{};
			Object* new_object = ((Object*)t_object);
			new_object->name = name;
			parent->transform.children.push_back(new_object);
			new_object->parent = parent;
			return new_object;
		}
	}
}