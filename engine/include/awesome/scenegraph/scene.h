#pragma once 

#include <vector>

namespace Awesome
{
	namespace Scenegraph
	{
		class Object;

		class Scene
		{
		private:
			static Scene* singleton;

		protected:
			std::vector<Object*> objects;

		public:
			Scene();

			static Scene* instance();

			template <class T>
			static Object* spawn(std::string name);
			template <class T>
			static Object* spawn(std::string name, Object* parent);
		};
	}
}