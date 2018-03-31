#pragma once

/*
	Simple unique id 
	useful to identify objects and components
*/

namespace Awesome
{
	class UniqueId
	{
	private:
		static unsigned int value_counter;
		unsigned int value;

	public:
		UniqueId() {
			value = ++value_counter;
		}

		bool operator==(const UniqueId& other_id)
		{
			return value = other_id.value;
		}
	};
}