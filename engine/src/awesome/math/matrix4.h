#pragma once

namespace awesome
{
	template <typename T>
	class matrix4_t
	{
		static const matrix4_t zero;
		static const matrix4_t identity;

		// num of rows
		const std::size_t rows = 4;
		// num of columns
		const std::size_t columns = 4;

		// matrix data
		union
		{
			struct
			{
				T m00, m01, m02, m03;
				T m10, m11, m12, m13;
				T m20, m21, m22, m23;
				T m30, m31, m32, m33;
			};

			T data[4 * 4];
		};


	};
}