#pragma once 

#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>

namespace awesome
{
	template<std::size_t N, typename T>
	struct base_vector
	{
		// vector size
		const std::size_t length = N;

		// store data into a managed array
		std::array<T, N> data;

		// default constructor
		base_vector()
		{
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_vector(const T t_value)
		{
			data.fill(t_value);
		}

		// construct with initialzie list
		base_vector(const std::initializer_list<T>& t_args)
		{
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = t_args.begin(); it != t_args.end() && i < length; ++it)
			{
				data[i] = *it;
				++i;
			}
		}

		// copy constructor
		base_vector(const base_vector<N, T>& t_other)
		{
			data = t_other.data;
		}

		// templated copy constructor
		template<std::size_t M>
		base_vector(const base_vector<M, T>& t_other)
		{
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = t_other.data.begin(); it != t_other.data.end() && i < length; ++it)
			{
				data[i] = *it;
				++i;
			}
		}

		// return the vector length
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
			return data.at(t_i);
		}

		T operator() (const unsigned int t_i) const
		{
			return data.at(t_i);
		}

		// compute the magnitude
		// magnitude = x1 * x1 + x2 * x2 + ... + xn * xn
		T magnitude() const
		{
			T result = {};
			for (unsigned int i = 0; i < length; ++i)
				result += data[i] * data[i];
			return static_cast<T>(sqrt(result));
		}

		// compute the distance between another vector
		T distance(const base_vector<N, T> & t_other) const
		{
			return (*this - t_other).magnitude();
		}

		// dot product
		T dot(const base_vector<N, T> & t_other) const
		{
			return (*this)* t_other;
		}

		// normalize the vector
		base_vector<N, T> normalize()
		{
			return (*this *= (static_cast<T>(1.0) / magnitude()));
		}

		base_vector<N, T> project(const base_vector<N, T> & t_v)
		{
			T d = t_v * t_v;
			assert(d != static_cast<T>(0.0));
			return t_v * ((*this * t_v) / d);
		}

		base_vector<N, T> reject(const base_vector<N, T> & t_v)
		{
			T d = t_v * t_v;
			assert(d != static_cast<T>(0.0));
			return (*this - t_v) * ((*this * t_v) / d);
		}

		// Operators overloading 

		base_vector<N, T> & operator= (const base_vector<N, T> & t_other)
		{
			// check for self-assignment
			if (this == &t_other)
				return *this;

			// copy 
			data = t_other.data;
			return *this;
		}

		bool operator== (const base_vector<N, T> & t_other) const
		{
			return (*this).data == t_other.data;
		}

		bool operator!= (const base_vector<N, T> & t_other) const
		{
			return !(*this == t_other);
		}

		base_vector<N, T>& operator+= (const base_vector<N, T> & t_other)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] += t_other[i];
			return *this;
		}

		base_vector<N, T>& operator-= (const base_vector<N, T> & t_other)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] -= t_other[i];
			return *this;
		}

		base_vector<N, T>& operator*= (const T t_s)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] *= t_s;
			return *this;
		}

		base_vector<N, T>& operator/= (const T t_s)
		{
			assert(t_s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_s;
			for (unsigned int i = 0; i < length; i++)
				data[i] *= f;
			return *this;
		}

		base_vector<N, T> operator- () const
		{
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = -data[i];
			return v;
		}

		base_vector<N, T> operator+ (const base_vector<N, T> & t_w) const
		{
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] + t_w[i];
			return v;
		}

		base_vector<N, T> operator- (const base_vector<N, T> & t_w) const
		{
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] - t_w[i];
			return v;
		}

		base_vector<N, T> operator* (const T t_s) const
		{
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] * t_s;
			return v;
		}

		base_vector<N, T> operator/ (const T t_s) const
		{
			assert(s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_s;
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] * f;
			return v;
		}

		// dot product 
		T operator*(const base_vector<N, T> & t_v) const
		{
			T dot{};
			for (unsigned int i = 0; i < length; i++)
				dot += data[i] * t_v[i];
			return dot;
		}
	};

	template<std::size_t N, class T>
	inline base_vector<N, T> operator* (const T t_s, const base_vector<N, T> & t_v)
	{
		base_vector<N, T> w;
		for (unsigned int i = 0; i < N; i++)
			w[i] = t_v[i] * t_s;
		return w;
	}
}