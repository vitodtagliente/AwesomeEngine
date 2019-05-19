#pragma once

#include "base_point.h"

namespace awesome
{
	// undefined order zero point
	template<typename T>
	struct base_point<0, T>;

	// order 2 point
	template<typename T>
	struct base_point2 : public base_point<2, T>
	{
		// inherits base class constructors
		using base_point<2, T>::base_point;

		base_point2() 
			: base_point<2, T>() 
		{
		
		}

		T& x = base_point<2, T>::data[0];
		T& y = base_point<2, T>::data[1];

		base_point2(const T _x, const T _y)
		{
			x = t_x;
			y = t_y;
		}

		base_point2& operator= (const base_point2& t_other) 
		{
			data = t_other.data;
		}
	};

	// order 3 point
	template<typename T>
	struct base_point3 : public base_point<3, T>
	{
		// inherits base class constructors
		using base_point<3, T>::base_point;

		base_point3() 
			: base_point<3, T>() 
		{
		
		}

		T& x = base_point<3, T>::data[0];
		T& y = base_point<3, T>::data[1];
		T& z = base_point<3, T>::data[2];

		base_point3(const T t_x, const T t_y, const T t_z)
		{
			x = t_x;
			y = t_y;
			z = t_z;
		}

		base_point3& operator= (const base_point3& other) 
		{
			data = other.data;
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