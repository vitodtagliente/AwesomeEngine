#pragma once

namespace Dreamkeeper
{
	namespace Core
	{
		struct BaseElement
		{
			unsigned int id = 0;

			bool isValid() const {
				return id > 0;
			}
		};
	}
}