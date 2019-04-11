#pragma once

#include "vec2.h"

namespace awesome
{
	namespace math
	{
		template <typename T>
		struct tvec3
		{
			T x{}, y{}, z{};

			tvec3<T>() {}
			tvec3<T>(const T n_X, const T n_Y, const T n_Z) {
				x = n_X;
				y = n_Y;
				z = n_Z;
			}
			tvec3<T>(const tvec3<T>& other) {
				x = other.x;
				y = other.y;
				z = other.z;
			}
			tvec3<T>(const tvec2<T>& other) {
				x = other.x;
				y = other.y;
				z{};
			}

			T magnitude() const {
				return static_cast<T>(sqrt(x * x + y * y + z * z));
			}

			T distance(const tvec3<T>& other) const {
				return (*this - other).magnitude();
			}

			T dot(const tvec3<T>& other) const {
				return (*this) * other;
			}

			tvec3<T> cross(const tvec3<T>& other) const {
				return tvec3<T>(
					y*other.z - z * other.y,
					z*other.x - x * other.z,
					x*other.y - y * other.x
				);
			}

			// operators overloading

			tvec3<T>& operator= (const tvec3<T>& other) {
				if (this != &other) {
					x = other.x;
					y = other.y;
					z = other.z;
				}
				return *this;
			}

			bool operator== (const tvec3<T>& other) const {
				return x == other.x && y == other.y && z == other.z;
			}

			bool operator!= (const tvec3<T>& other) const {
				return x != other.x || y != other.y || z != other.z;
			}

			tvec3<T>& operator+= (const tvec3<T>& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}

			tvec3<T>& operator-= (const tvec3<T>& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}

			tvec3<T>& operator*= (const T value) {
				x *= value;
				y *= value;
				z *= value;
				return *this;
			}

			tvec3<T>& operator/= (const T value) {
				assert(value != static_cast<T>(0.0));

				T d = static_cast<T>(1.0) / value;
				x *= d;
				y *= d;
				z *= d;
				return *this;
			}

			tvec3<T> operator- () const {
				return tvec3<T>(-x, -y, -z);
			}

			tvec3<T> operator- (const tvec3<T>& other) const
			{
				return tvec3<T>(x - other.x, y - other.y, z - other.z);
			}

			tvec3<T> operator+ (const tvec3<T>& other) const
			{
				return tvec3<T>(x + other.x, y + other.y, z + other.z);
			}

			T operator* (const tvec3<T>& other) const {
				return x * other.x + y * other.y + z * other.z;
			}

			static const tvec3<T> zero;
			static const tvec3<T> up;
			static const tvec3<T> right;
		};

		template <typename T>
		inline tvec3<T> operator* (const T value, const tvec3<T>& other) {
			return other * value;
		}

		template <typename T>
		const tvec3<T> tvec3<T>::zero = tvec3<T>(static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0));
		template <typename T>
		const tvec3<T> tvec3<T>::up = tvec3<T>(static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0));
		template <typename T>
		const tvec3<T> tvec3<T>::right = tvec3<T>(static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0));

		typedef tvec3<float> vec3;
		typedef tvec3<float> fvec3;
		typedef tvec3<double> dvec3;
		typedef tvec3<int> ivec3;

	}
}