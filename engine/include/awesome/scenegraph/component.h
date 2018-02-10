#pragma once 

namespace Awesome
{
	namespace Scenegraph
	{
		class Object;

		class Component
		{
		private:
			static unsigned int id_counter;

		protected:
			Object* owner{ nullptr };

		public:
			Component();
			Component(Object* component_owner);

			unsigned int id{ 0 };
						
			virtual void init() = 0;
			virtual void update(float delta_time) = 0;
		};
	}
}