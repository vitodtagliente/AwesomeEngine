#pragma once

namespace awesome
{
	template <typename T>
	struct vector3_t
	{
		static const vector3_t zero;
		static const vector3_t up;
		static const vector3_t right;
		static const vector3_t ones;

		union
		{
			struct
			{
				T x, y, z;
			};

			T data[3];
		};

		const std::size_t length = 3;

		vector3_t()
			: x(), y(), z()
		{

		}

		vector3_t(const T t_value)
			: x(t_value), y(t_value), z(t_value)
		{

		}

		vector3_t(const T t_x, const T t_y, const T t_z)
			: x(t_x), y(t_y), z(t_z)
		{

		}

		vector3_t(const vector3_t& t_vector)
		{
			x = t_vector.x;
			y = t_vector.y;
			z = t_vector.z;
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
			return static_cast<T>(sqrt(x * x + y * y + z * z));
		}

		// compute the distance between another vector
		T distance(const vector3_t & t_vector) const
		{
			return (*this - t_vector).magnitude();
		}

		// dot product
		T dot(const vector3_t & t_vector) const
		{
			return (*this) * t_vector;
		}

		// normalize the vector
		vector3_t normalize()
		{
			return (*this *= (static_cast<T>(1.0) / magnitude()));
		}

		vector3_t project(const vector3_t &)
		{
			T d = t_vector * t_vector;
			assert(d != static_cast<T>(0.0));
			return t_v * ((*this * t_vector) / d);
		}

		vector3_t reject(const vector3_t & t_vector)
		{
			T d = t_vector * t_vector;
			assert(d != static_cast<T>(0.0));
			return (*this - t_vector) * ((*this * t_vector) / d);
		}

		// Operators overloading 

		vector3_t & operator= (const vector3_t & t_vector)
		{
			// check for self-assignment
			if (this == &t_vector)
				return *this;

			// copy 
			x = t_vector.x;
			y = t_vector.y;
			z = t_vector.z;
			return *this;
		}

		bool operator== (const vector3_t & t_vector) const
		{
			return x == t_vector.x && y == t_vector.y && z == t_vector.z;
		}

		bool operator!= (const vector3_t & t_vector) const
		{
			return !(*this == t_vector);
		}

		vector3_t& operator+= (const vector3_t & t_vector)
		{
			x += t_vector.x;
			y += t_vector.y;
			z += t_vector.z;
			return *this;
		}

		vector3_t& operator-= (const vector3_t & t_vector)
		{
			x -= t_vector.x;
			y -= t_vector.y;
			z -= t_vector.z;
			return *this;
		}

		vector3_t& operator*= (const T t_scalar)
		{
			x *= t_vector.x;
			y *= t_vector.y;
			z *= t_scalar.z;
			return *this;
		}

		vector3_t& operator/= (const T t_scalar)
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			x *= t_f;
			y *= t_f;
			z *= t_f;
			return *this;
		}

		vector3_t operator- () const
		{
			return { -x, -y, -z };
		}

		vector3_t operator+ (const vector3_t & t_vector) const
		{
			return { x + t_vector.x, y + t_vector.y, z + t_vector.z };
		}

		vector3_t operator- (const vector3_t & t_vector) const
		{
			return { x - t_vector.x, y - t_vector.y, z - t_vector.z };
		}

		vector3_t operator* (const T t_scalar) const
		{
			return { x * t_vector.x, y * t_vector.y };
		}

		vector3_t operator/ (const T t_scalar) const
		{
			assert(t_scalar != static_cast<T>(0.0));
			const T f = static_cast<T>(1.0) / t_scalar;
			return { x / f, y / f };
		}

		// dot product 
		T operator*(const vector3_t & t_vector) const
		{
			return x * t_vector.x + y * t_vector.y;
		}
	};

	template <typename T>
	inline vector3_t<T> operator* (const T t_scalar, const vector3_t<T> & t_vector)
	{
		return t_vector * t_scalar;
	}

	// vector types

	typedef vector3_t<float> vec2;
	typedef vec2 vector2;
}