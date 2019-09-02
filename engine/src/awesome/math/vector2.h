#pragma once
#pragma warning(disable : 4201)

#include <cstddef>

namespace awesome
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

		vector2_t(const T t_value)
			: x(t_value), y(t_value)
		{

		}

		vector2_t(const T t_x, const T t_y)
			: x(t_x), y(t_y)
		{

		}

		vector2_t(const vector2_t& t_vector)
		{
			x = t_vector.x;
			y = t_vector.y;
		}

		std::size_t size() const
		{
			return length;
		}

		// return the i-index component
		T& operator[] (const unsigned int t_i)
		{
			return data[t_i];
		}

		T operator[] (const unsigned int t_i) const
		{
			return data[t_i];
		}

		T& operator() (const unsigned int t_i)
		{
			return data[t_i];
		}

		T operator() (const unsigned int t_i) const
		{
			return data[t_i];
		}

		// compute the magnitude
		// magnitude = x1 * x1 + x2 * x2 + ... + xn * xn
		T magnitude() const
		{
			return static_cast<T>(sqrt(x * x + y * y));
		}

		// compute the distance between another vector
		T distance(const vector2_t & t_vector) const
		{
			return (*this - t_vector).magnitude();
		}

		// dot product
		T dot(const vector2_t & t_vector) const
		{
			return (*this) * t_vector;
		}

		// normalize the vector
		vector2_t normalize()
		{
			return (*this *= (static_cast<T>(1.0) / magnitude()));
		}

		vector2_t project(const vector2_t & )
		{
			T d = t_vector * t_vector;
			assert(d != static_cast<T>(0.0));
			return t_v * ((*this * t_vector) / d);
		}

		vector2_t reject(const vector2_t & t_vector)
		{
			T d = t_vector * t_vector;
			assert(d != static_cast<T>(0.0));
			return (*this - t_vector) * ((*this * t_vector) / d);
		}

		// Operators overloading 

		vector2_t & operator= (const vector2_t & t_vector)
		{
			// check for self-assignment
			if (this == &t_vector)
				return *this;

			// copy 
			x = t_vector.x;
			y = t_vector.y;
			return *this;
		}

		bool operator== (const vector2_t & t_vector) const
		{
			return x == t_vector.x && y == t_vector.y;
		}

		bool operator!= (const vector2_t & t_vector) const
		{
			return !(*this == t_vector);
		}

		vector2_t& operator+= (const vector2_t & t_vector)
		{
			x += t_vector.x;
			y += t_vector.y;
			return *this;
		}

		vector2_t& operator-= (const vector2_t & t_vector)
		{
			x -= t_vector.x;
			y -= t_vector.y;
			return *this;
		}

		vector2_t& operator*= (const T t_scalar)
		{
			x *= t_scalar;
			y *= t_scalar;
			return *this;
		}

		vector2_t& operator/= (const T t_scalar)
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			x *= t_f;
			y *= t_f;
			return *this;
		}

		vector2_t operator- () const
		{
			return { -x, -y };
		}

		vector2_t operator+ (const vector2_t & t_vector) const
		{
			return { x + t_vector.x, y + t_vector.y };
		}

		vector2_t operator- (const vector2_t & t_vector) const
		{
			return { x - t_vector.x, y - t_vector.y };
		}

		vector2_t operator* (const T t_scalar) const
		{
			return { x * t_scalar, y * t_scalar };
		}

		vector2_t operator/ (const T t_scalar) const
		{
			assert(t_scalar != static_cast<T>(0.0));
			const T f = static_cast<T>(1.0) / t_scalar;
			return { x * f, y * f };
		}

		// dot product 
		T operator*(const vector2_t & t_vector) const
		{
			return x * t_vector.x + y * t_vector.y;
		}
	};

	template <typename T>
	inline vector2_t<T> operator* (const T t_scalar, const vector2_t<T> & t_vector)
	{
		return t_vector * t_scalar;
	}

	template<typename T> const vector2_t<T> vector2_t<T>::zero = vector2_t<T>(0.0, 0.0);
	template<typename T> const vector2_t<T> vector2_t<T>::up = vector2_t<T>(0.0, 1.0);
	template<typename T> const vector2_t<T> vector2_t<T>::right = vector2_t<T>(1.0, 0.0);
	template<typename T> const vector2_t<T> vector2_t<T>::ones = vector2_t<T>(1.0, 1.0);

	// vector types

	typedef vector2_t<float> vec2;
	typedef vec2 vector2;
}