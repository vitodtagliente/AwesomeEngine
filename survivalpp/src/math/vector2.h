/// Copyright (c) Vito Domenico Tagliente

#pragma once
#pragma warning(disable : 4201)

#include <cassert>
#include <cstddef>

namespace math
{
	template <typename T>
	struct vector2_t
	{
		static const vector2_t zero;
		static const vector2_t up;
		static const vector2_t right;
		static const vector2_t ones;

		union
		{
			struct
			{
				T x, y;
			};

			T data[2];
		};

		const std::size_t length = 2;

		vector2_t()
			: x(), y()
		{

		}

		vector2_t(const T value)
			: x(value), y(value)
		{

		}

		vector2_t(const T x, const T y)
			: x(x), y(y)
		{

		}

		vector2_t(const vector2_t& vector)
		{
			x = vector.x;
			y = vector.y;
		}

		std::size_t size() const
		{
			return length;
		}

		// return the i-index component
		T& operator[] (const unsigned int i)
		{
			return data[i];
		}

		T operator[] (const unsigned int i) const
		{
			return data[i];
		}

		T& operator() (const unsigned int i)
		{
			return data[i];
		}

		T operator() (const unsigned int i) const
		{
			return data[i];
		}

		// compute the magnitude
		// magnitude = x1 * x1 + x2 * x2 + ... + xn * xn
		T magnitude() const
		{
			return static_cast<T>(sqrt(x * x + y * y));
		}

		// compute the distance between another vector
		T distance(const vector2_t& vector) const
		{
			return (*this - vector).magnitude();
		}

		// dot product
		T dot(const vector2_t& vector) const
		{
			return (*this) * vector;
		}

		// normalize the vector
		vector2_t normalize()
		{
			const T mag = magnitude();
			if (mag != static_cast<T>(0.0))
			{
				(*this *= (static_cast<T>(1.0) / mag));
			}
			return *this;
		}

		vector2_t project(const vector2_t& vector)
		{
			T d = vector * vector;
			assert(d != static_cast<T>(0.0));
			return vector * ((*this * vector) / d);
		}

		vector2_t reject(const vector2_t& vector)
		{
			T d = vector * vector;
			assert(d != static_cast<T>(0.0));
			return (*this - vector) * ((*this * vector) / d);
		}

		// Operators overloading 

		vector2_t& operator= (const vector2_t& vector)
		{
			// check for self-assignment
			if (this == &vector)
				return *this;

			// copy 
			x = vector.x;
			y = vector.y;
			return *this;
		}

		bool operator== (const vector2_t& vector) const
		{
			return x == vector.x && y == vector.y;
		}

		bool operator!= (const vector2_t& vector) const
		{
			return !(*this == vector);
		}

		vector2_t& operator+= (const vector2_t& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		vector2_t& operator-= (const vector2_t& vector)
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		vector2_t& operator*= (const T scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		vector2_t& operator/= (const T scalar)
		{
			assert(scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / scalar;
			x *= f;
			y *= f;
			return *this;
		}

		vector2_t operator- () const
		{
			return { -x, -y };
		}

		vector2_t operator+ (const vector2_t& vector) const
		{
			return { x + vector.x, y + vector.y };
		}

		vector2_t operator- (const vector2_t& vector) const
		{
			return { x - vector.x, y - vector.y };
		}

		vector2_t operator* (const T scalar) const
		{
			return { x * scalar, y * scalar };
		}

		vector2_t operator/ (const T scalar) const
		{
			assert(scalar != static_cast<T>(0.0));
			const T f = static_cast<T>(1.0) / scalar;
			return { x * f, y * f };
		}

		// dot product 
		T operator*(const vector2_t& vector) const
		{
			return x * vector.x + y * vector.y;
		}
	};

	template <typename T>
	inline vector2_t<T> operator* (const T scalar, const vector2_t<T>& vector)
	{
		return vector * scalar;
	}

	template<typename T> const vector2_t<T> vector2_t<T>::zero = vector2_t<T>(0.0, 0.0);
	template<typename T> const vector2_t<T> vector2_t<T>::up = vector2_t<T>(0.0, 1.0);
	template<typename T> const vector2_t<T> vector2_t<T>::right = vector2_t<T>(1.0, 0.0);
	template<typename T> const vector2_t<T> vector2_t<T>::ones = vector2_t<T>(1.0, 1.0);

	// vector types

	typedef vector2_t<float> vec2;
	typedef vec2 vector2;
	typedef vector2_t<int> vec2i;
	typedef vec2i vector2i;
}