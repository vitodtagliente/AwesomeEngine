#include <awesome/scenegraph/scene_reader.h>

/*
	TODO: improve this
*/

namespace Awesome
{
	namespace Scenegraph
	{
		SceneReader::SceneReader(Object* begin_object)
		{
			this->begin_object = begin_object;
			current_object = begin_object;
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
				else
				{
					reading = false;
					return nullptr;
				}
			}
			else
			{
				reading = false;
				return nullptr;
			}
		}
	}
}