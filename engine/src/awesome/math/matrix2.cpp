#include "matrix2.h"

namespace awesome
{
	template<typename T> const matrix2_t<T> matrix2_t<T>::zero = matrix2_t<T>(0.0);
	template<typename T> const matrix2_t<T> matrix2_t<T>::identity = matrix2_t<T>(
		1.0, 0.0,
		0.0, 1.0
	);
}