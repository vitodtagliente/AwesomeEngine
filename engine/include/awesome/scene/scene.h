#pragma once 

#include "../object.h"

namespace Awesome
{
	class Scene : public Object
	{
	public:

		Scene();

		/*
		TODO: add IO operations
		- load from file
		- save to file
		*/

		// release all the scene resources
		void unload();
	};
}