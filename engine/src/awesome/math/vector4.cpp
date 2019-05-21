#include "vector4.h"

namespace awesome
{
	template<typename T> const vector4_t<T> vector4_t<T>::zero = vector4_t<T>(0.0, 0.0, 0.0, 0.0);
	template<typename T> const vector4_t<T> vector4_t<T>::ones = vector4_t<T>(1.0, 1.0, 1.0, 1.0);
}