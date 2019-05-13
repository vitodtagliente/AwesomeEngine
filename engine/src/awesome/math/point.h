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
		base_point() {
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_point(const T value) {
			data.fill(value);
		}

		// construct with initialzie list
		base_point(const std::initializer_list<T>& args) {
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = args.begin(); it != args.end() && i < length; ++it) {
				data[i] = *it;
				++i;
			}
		}
		
		// templated copy constructor
		template<std::size_t M>
		base_point(const base_point<M, T>& other)
		{
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = other.data.begin(); it != other.data.end() && i < length; ++it)
			{
				data[i] = *it;
				++i;
			}
		}
		
		// return the point length
		std::size_t size() const {
			return length;
		}

		// return the i-index component
		T& operator[] (const unsigned int i) {
			return data[i];
		}

		T operator[] (const unsigned int i) const {
			return data[i];
		}

		T& operator() (const unsigned int i)
		{
			return data.at(i);
		}

		T operator() (const unsigned int i) const
		{
			return data.at(i);
		}

		base_point<N, T>& operator= (const base_point<N, T>& other) {
			/* check for self-assignment */
			if (this == &other)
				return *this;

			/* copy */
			data = other.data;
			return *this;
		}

		bool operator== (const base_point<N, T>& other) const {
			return (*this).data == other.data;
		}

		bool operator!= (const base_point<N, T>& other) const {
			return !(*this == other);
		}
	};

	// undefined order zero point
	template<typename T>
	struct base_point<0, T>;

	// order 2 point
	template<typename T>
	struct base_point2 : public base_point<2, T>
	{
		// inherits base class constructors
		using base_point<2, T>::base_point;

		base_point2() :base_point<2, T>() {}

		T& x = base_point<2, T>::data[0];
		T& y = base_point<2, T>::data[1];

		base_point2(const T _x, const T _y)
		{
			base_point<2, T>::data[0] = _x;
			base_point<2, T>::data[1] = _y;
		}

		base_point2& operator= (const base_point2& other) {
			base_point<2, T>::data = other.data;
		}
	};

	// order 3 point
	template<typename T>
	struct base_point3 : public base_point<3, T>
	{
		// inherits base class constructors
		using base_point<3, T>::base_point;

		base_point3() :base_point<3, T>() {}

		T& x = base_point<3, T>::data[0];
		T& y = base_point<3, T>::data[1];
		T& z = base_point<3, T>::data[2];

		base_point3(const T _x, const T _y, const T _z)
		{
			base_point<3, T>::data[0] = _x;
			base_point<3, T>::data[1] = _y;
			base_point<3, T>::data[2] = _z;
		}

		base_point3& operator= (const base_point3& other) {
			base_point<3, T>::data = other.data;
		}
	};

	// point types
	typedef base_point2<float> point2;
	typedef base_point3<float> point3;

	typedef point2 fpoint2;
	typedef point3 fpoint3;

	typedef base_point2<double> dpoint2;
	typedef base_point3<double> dpoint3;
	
	typedef base_point2<int> ipoint2;
	typedef base_point3<int> ipoint3;

	typedef base_point2<unsigned int> upoint2;
	typedef base_point3<unsigned int> upoint3;
};