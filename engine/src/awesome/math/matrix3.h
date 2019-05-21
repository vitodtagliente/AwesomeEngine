#pragma once

namespace awesome
{
	template <typename T>
	class matrix3_t
	{
		// num of rows
		const std::size_t rows = 3;
		// num of columns
		const std::size_t columns = 3;

		// matrix data
		T data[3][3];


	};
}