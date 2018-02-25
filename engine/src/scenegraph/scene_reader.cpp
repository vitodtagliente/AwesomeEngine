#include <awesome/scenegraph/scene_reader.h>

namespace Awesome
{
	namespace Scenegraph
	{
		SceneReader::SceneReader(Scene* selected_scene)
		{
			current_object = selected_scene;
		}

		Object* const SceneReader::next()
		{
			if (current_object->parent() == nullptr) 
			{
				auto children = current_object->children();
				if (children.size() <= 0)
					return nullptr;

				child_index++;
				if(child_index < children.size())
					return children[child_index];
				else return nullptr;
			}
			else
			{
				return nullptr;
			}
		}
	}
}