#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>

namespace awesome
{
	template <std::size_t N, typename T>
	struct base_point
	{
		// vector size
		const std::size_t length = N;

		// store data into a managed array
		std::array<T, N> data;

		// default constructor
		base_point() 
		{
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_point(const T t_value) 
		{
			data.fill(t_value);
		}

		// construct with initialzie list
		base_point(const std::initializer_list<T>& t_args) 
		{
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = t_args.begin(); it != t_args.end() && i < length; ++it) 
			{
				data[i] = *it;
				++i;
			}
		}

		// templated copy constructor
		template<std::size_t M>
		base_point(const base_point<M, T>& t_other)
		{
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = t_other.data.begin(); it != t_other.data.end() && i < length; ++it)
			{
				data[i] = *it;
				++i;
			}
		}

		// return the point length
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

		base_point<N, T>& operator= (const base_point<N, T>& t_other) 
		{
			/* check for self-assignment */
			if (this == &t_other)
				return *this;

			/* copy */
			data = t_other.data;
			return *this;
		}

		bool operator== (const base_point<N, T> & t_other) const 
		{
			return (*this).data == t_other.data;
		}

		bool operator!= (const base_point<N, T> & t_other) const 
		{
			return !(*this == t_other);
		}
	};
};