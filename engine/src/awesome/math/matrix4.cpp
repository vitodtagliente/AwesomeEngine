#include "matrix4.h"

namespace awesome
{
	template<typename T> const matrix4_t<T> matrix4_t<T>::zero = matrix4_t<T>(0.0);
	template<typename T> const matrix4_t<T> matrix4_t<T>::identity = matrix4_t<T>(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}