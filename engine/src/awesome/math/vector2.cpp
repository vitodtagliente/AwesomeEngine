#include "vector2.h"

namespace awesome
{
	template<typename T> const vector2_t<T> vector2_t<T>::zero = vector2_t<T>(0.0, 0.0);
	template<typename T> const vector2_t<T> vector2_t<T>::up = vector2_t<T>(0.0, 1.0);
	template<typename T> const vector2_t<T> vector2_t<T>::right = vector2_t<T>(1.0, 0.0);
	template<typename T> const vector2_t<T> vector2_t<T>::ones = vector2_t<T>(1.0, 1.0);
}