#pragma once 

#include "object.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class Component
		{
			friend class Object;

		private:
			static unsigned int id_counter;
			Object* owner_object{ nullptr };

		public:
			unsigned int id{ 0 };

			Component();

			/* return the owner object */
			Object* owner() { return owner_object; }

			/* engine events */
			virtual void init() = 0;
			virtual void update(float delta_time) = 0;		

			bool operator== (const Component& other);
		};
	}
}