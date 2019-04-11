#pragma once

#include <cassert>
#include <cmath>
#include "../types.h"

namespace awesome
{
	namespace math
	{
		template <typename T>
		struct tvec2
		{
			T x{}, y{};

			tvec2<T>(){}
			tvec2<T>(const T n_X, const T n_Y) {
				x = n_X;
				y = n_Y;
			}
			tvec2<T>(const tvec2<T>& other) {
				x = other.x;
				y = other.y;
			}

			T magnitude() const {
				return static_cast<T>(sqrt(x * x + y * y));
			}

			T distance(const tvec2<T>& other) const {
				return (*this - other).magnitude();
			}

			T dot(const tvec2<T>& other) const {
				return (*this) * other;
			}

			// operators overloading

			tvec2<T>& operator= (const tvec2<T>& other) {
				if (this != &other) {
					x = other.x;
					y = other.y;
				}				
				return *this;
			}

			bool operator== (const tvec2<T>& other) const {
				return x == other.x && y == other.y;
			}

			bool operator!= (const tvec2<T>& other) const {
				return x != other.x || y != other.y;
			}

			tvec2<T>& operator+= (const tvec2<T>& other) {
				x += other.x;
				y += other.y;
				return *this;
			}

			tvec2<T>& operator-= (const tvec2<T>& other) {
				x -= other.x;
				y -= other.y;
				return *this;
			}

			tvec2<T>& operator*= (const T value)  {
				x *= value;
				y *= value;
				return *this;
			}

			tvec2<T>& operator/= (const T value) {
				assert(value != static_cast<T>(0.0));

				T d = static_cast<T>(1.0) / value;
				x *= d;
				y *= d;
				return *this;
			}

			tvec2<T> operator- () const {
				return tvec2<T>(-x, -y);
			}
			
			tvec2<T> operator- (const tvec2<T>& other) const 
			{
				return tvec2<T>(x - other.x, y - other.y);
			}

			tvec2<T> operator+ (const tvec2<T>& other) const
			{
				return tvec2<T>(x + other.x, y + other.y);
			}

			T operator* (const tvec2<T>& other) const {
				return x * other.x + y * other.y;
			}

			static const tvec2<T> zero;
			static const tvec2<T> up;
			static const tvec2<T> right;
		};

		template <typename T>
		inline tvec2<T> operator* (const T value, const tvec2<T>& other) {
			return other * value;
		}

		template <typename T>
		const tvec2<T> tvec2<T>::zero = tvec2<T>(static_cast<T>(0.0), static_cast<T>(0.0));
		template <typename T>
		const tvec2<T> tvec2<T>::up = tvec2<T>(static_cast<T>(0.0), static_cast<T>(1.0));
		template <typename T>
		const tvec2<T> tvec2<T>::right = tvec2<T>(static_cast<T>(1.0), static_cast<T>(0.0));

		typedef tvec2<float> vec2;
		typedef tvec2<float> fvec2;
		typedef tvec2<double> dvec2;
		typedef tvec2<int> ivec2;
		
	}
}