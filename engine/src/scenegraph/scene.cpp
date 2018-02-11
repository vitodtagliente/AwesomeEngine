#include <awesome/scenegraph/scene.h>

namespace Awesome
{
	namespace Scenegraph
	{
		void Scene::addObject(Object* new_object)
		{
			objects.push_back(new_object);
		}

		void Scene::addObject(Object* new_object, Object* parent)
		{
			parent->transform.children.push_back(new_object);
			new_object->transform.parent = parent;
		}
	}
}