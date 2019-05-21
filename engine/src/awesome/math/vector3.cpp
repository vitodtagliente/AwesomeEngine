#include "vector3.h"

namespace awesome
{
	template<typename T> const vector3_t<T> vector3_t<T>::zero = vector3_t<T>(0.0, 0.0, 0.0);
	template<typename T> const vector3_t<T> vector3_t<T>::up = vector3_t<T>(0.0, 1.0, 0.0);
	template<typename T> const vector3_t<T> vector3_t<T>::right = vector3_t<T>(1.0, 0.0, 0.0);
	template<typename T> const vector3_t<T> vector3_t<T>::forward = vector3_t<T>(0.0, 0.0, -1.0);
	template<typename T> const vector3_t<T> vector3_t<T>::ones = vector3_t<T>(1.0, 1.0, 1.0);
}