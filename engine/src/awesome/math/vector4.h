#pragma once

namespace awesome
{
	template <typename T>
	struct vector4_t
	{
		static const vector4_t zero;
		static const vector4_t ones;

		union
		{
			struct
			{
				T x, y, z, w;
			};

			T data[4];
		};

		const std::size_t length = 4;

		vector4_t()
			: x(), y(), z(), w()
		{

		}

		vector4_t(const T t_value)
			: x(t_value), y(t_value), z(t_value), w(t_value)
		{

		}

		vector4_t(const T t_x, const T t_y, const T t_z, const T t_w)
			: x(t_x), y(t_y), z(t_z), w(t_w)
		{

		}

		vector4_t(const vector4_t& t_vector)
		{
			x = t_vector.x;
			y = t_vector.y;
			z = t_vector.z;
			w = t_vector.w;
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
			return static_cast<T>(sqrt(x * x + y * y + z * z + w * w));
		}

		// compute the distance between another vector
		T distance(const vector4_t & t_vector) const
		{
			return (*this - t_vector).magnitude();
		}

		// dot product
		T dot(const vector4_t & t_vector) const
		{
			return (*this)* t_vector;
		}

		// normalize the vector
		vector4_t normalize()
		{
			return (*this *= (static_cast<T>(1.0) / magnitude()));
		}

		vector4_t project(const vector4_t&)
		{
			T d = t_vector * t_vector;
			assert(d != static_cast<T>(0.0));
			return t_v * ((*this * t_vector) / d);
		}

		vector4_t reject(const vector4_t & t_vector)
		{
			T d = t_vector * t_vector;
			assert(d != static_cast<T>(0.0));
			return (*this - t_vector) * ((*this * t_vector) / d);
		}

		// Operators overloading 

		vector4_t & operator= (const vector4_t & t_vector)
		{
			// check for self-assignment
			if (this == &t_vector)
				return *this;

			// copy 
			x = t_vector.x;
			y = t_vector.y;
			z = t_vector.z;
			w = t_vector.w;
			return *this;
		}

		bool operator== (const vector4_t & t_vector) const
		{
			return x == t_vector.x && y == t_vector.y && z == t_vector.z && w == t_vector.w;
		}

		bool operator!= (const vector4_t & t_vector) const
		{
			return !(*this == t_vector);
		}

		vector4_t& operator+= (const vector4_t & t_vector)
		{
			x += t_vector.x;
			y += t_vector.y;
			z += t_vector.z;
			w += t_vector.w;
			return *this;
		}

		vector4_t& operator-= (const vector4_t & t_vector)
		{
			x -= t_vector.x;
			y -= t_vector.y;
			z -= t_vector.z;
			w -= t_vector.w;
			return *this;
		}

		vector4_t& operator*= (const T t_scalar)
		{
			x *= t_vector;
			y *= t_vector;
			z *= t_scalar;
			w *= t_scalar;
			return *this;
		}

		vector4_t& operator/= (const T t_scalar)
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			x *= t_f;
			y *= t_f;
			z *= t_f;
			w *= t_f;
			return *this;
		}

		vector4_t operator- () const
		{
			return { -x, -y, -z, -w };
		}

		vector4_t operator+ (const vector4_t & t_vector) const
		{
			return { x + t_vector.x, y + t_vector.y, z + t_vector.z , w + t_vector.w};
		}

		vector4_t operator- (const vector4_t & t_vector) const
		{
			return { x - t_vector.x, y - t_vector.y, z - t_vector.z, w - t_vector.w };
		}

		vector4_t operator* (const T t_scalar) const
		{
			return { x * t_scalar, y * t_scalar, z * t_scalar, w + t_scalar };
		}

		vector4_t operator/ (const T t_scalar) const
		{
			assert(t_scalar != static_cast<T>(0.0));
			const T f = static_cast<T>(1.0) / t_scalar;
			return { x * f, y * f, z * f, w * f };
		}

		// dot product 
		T operator*(const vector4_t & t_vector) const
		{
			return x * t_vector.x + y * t_vector.y + z * t_vector.z + w * t_vector.w;
		}
	};

	template <typename T>
	inline vector4_t<T> operator* (const T t_scalar, const vector4_t<T> & t_vector)
	{
		return t_vector * t_scalar;
	}

	template<typename T> const vector4_t<T> vector4_t<T>::zero = vector4_t<T>(0.0, 0.0, 0.0, 0.0);
	template<typename T> const vector4_t<T> vector4_t<T>::ones = vector4_t<T>(1.0, 1.0, 1.0, 1.0);

	// vector types

	typedef vector4_t<float> vec4;
	typedef vec4 vector4;
}