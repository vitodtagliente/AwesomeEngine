#pragma once

#include <string>
#include "program.h"

namespace Awesome
{
	namespace Rendering
	{
		class Material
		{
		private:

		public:
			Program* program;

			std::string projection{ "projection" };
			std::string view{ "view" };
			std::string model{ "model" };
		};
	}
}