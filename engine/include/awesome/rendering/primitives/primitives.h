#pragma once

#include <vector>

#include "cube.h"
#include "mesh.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"

namespace Awesome
{
	namespace Rendering
	{
		/*
			Primitive factory
		*/
		class Primitive
		{
		private:
			static std::vector<Mesh*> primitives;

			Primitive(){}

			template <class T>
			static T* findPrimitive()
			{
				for (auto it = primitives.begin(); it != primitives.end(); ++it)
				{
					T* current_primitive = dynamic_cast<T*>(*it);
					if (current_primitive != nullptr)
						return current_primitive;
				}
				return nullptr;
			}

		public:
			template <class T>
			static T* generate()
			{
				T* request_primitive = findPrimitive<T>();
				if (request_primitive != nullptr)
					return request_primitive;
				
				T* t_primitive = new T{};
				Mesh* new_primitive = dynamic_cast<Mesh*>(t_primitive);
				if (new_primitive != nullptr)
					primitives.push_back(t_primitive);
				return t_primitive;
			}

		};
	}
}