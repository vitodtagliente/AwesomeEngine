#include "matrix3.h"

namespace awesome
{
	template<typename T> const matrix3_t<T> matrix3_t<T>::zero = matrix3_t<T>(0.0);
	template<typename T> const matrix3_t<T> matrix3_t<T>::identity = matrix3_t<T>(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	);
}