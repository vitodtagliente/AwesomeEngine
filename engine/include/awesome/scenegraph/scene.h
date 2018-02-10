#pragma once 

#include <vector>

namespace Awesome
{
	namespace Scenegraph
	{
		class Object;

		class Scene
		{
		protected:
			std::vector<Object*> objects;

		public:
			Scene();

			template <class T>
			static Object* spawn(std::string name);
			template <class T>
			static Object* spawn(std::string name, Object* parent);
		};
	}
}