#pragma once

#include "base_vector.h"

namespace awesome
{
	// undefined order zero vector
	template<typename T>
	struct base_vector<0, T>;

	// order 2 vector
	template<typename T>
	struct base_vector2 : public base_vector<2, T>
	{
		// inherits base class constructors
		using base_vector<2, T>::base_vector;

		base_vector2() 
			: base_vector<2, T>() 
		{

		}

		T& x = base_vector<2, T>::data[0];
		T& y = base_vector<2, T>::data[1];

		base_vector2(const T t_x, const T t_y)
		{
			x = t_x;
			y = t_y;
		}

		base_vector2& operator= (const base_vector2& t_other)
		{
			data = t_other.data;
			return (*this);
		}

		static const base_vector2<T> zero;
		static const base_vector2<T> up;
		static const base_vector2<T> right;
	};

	template<typename T> const base_vector2<T> base_vector2<T>::zero = base_vector2<T>(0.0, 0.0);
	template<typename T> const base_vector2<T> base_vector2<T>::up = base_vector2<T>(0.0, 1.0);
	template<typename T> const base_vector2<T> base_vector2<T>::right = base_vector2<T>(1.0, 0.0);

	// order 3 vector
	template<typename T>
	struct base_vector3 : public base_vector<3, T>
	{
		// inherits base class constructors
		using base_vector<3, T>::base_vector;

		base_vector3() 
			: base_vector<3, T>() 
		{
		
		}

		T& x = base_vector<3, T>::data[0];
		T& y = base_vector<3, T>::data[1];
		T& z = base_vector<3, T>::data[2];

		base_vector3(const T t_x, const T t_y, const T t_z) 
		{
			x = t_x;
			y = t_y;
			z = t_z;
		}

		//cross product
		base_vector3<T> cross(const base_vector3<T>& t_v) const 
		{
			return base_vector3<T>(
				y * t_v.z - z * t_v.y,
				z * t_v.x - x * t_v.z,
				x * t_v.y - y * t_v.x
				);
		}

		// scalar triple product
		float triple(const  base_vector3<T> & t_v, const  base_vector3<T> & t_w) const 
		{
			return ((*this).cross(t_v))* t_w;
		}

		base_vector3& operator= (const base_vector3& t_other)
		{
			data = t_other.data;
			return (*this);
		}

		static const base_vector3<T> zero;
		static const base_vector3<T> up;
		static const base_vector3<T> right;
		static const base_vector3<T> forward;
	};

	template<typename T> const base_vector3<T> base_vector3<T>::zero = base_vector3<T>(0.0, 0.0, 0.0);
	template<typename T> const base_vector3<T> base_vector3<T>::up = base_vector3<T>(0.0, 1.0, 0.0);
	template<typename T> const base_vector3<T> base_vector3<T>::right = base_vector3<T>(1.0, 0.0, 0.0);
	template<typename T> const base_vector3<T> base_vector3<T>::forward = base_vector3<T>(0.0, 0.0, -1.0);

	// order 4 vector
	template<typename T>
	struct base_vector4 : public base_vector<4, T>
	{
		// inherits base class constructors
		using base_vector<4, T>::base_vector;

		base_vector4() 
			: base_vector<4, T>() 
		{
		
		}

		T& x = base_vector<4, T>::data[0];
		T& y = base_vector<4, T>::data[1];
		T& z = base_vector<4, T>::data[2];
		T& w = base_vector<4, T>::data[3];

		base_vector4(const T t_x, const T t_y, const T t_z, const T t_w) 
		{
			x = t_x;
			y = t_y;
			z = t_z;
			w = t_w;
		}

		base_vector4& operator= (const base_vector4& t_other)
		{
			data = t_other.data;
			return (*this);
		}

		static const base_vector4<T> zero;
	};

	template<typename T> const base_vector4<T> base_vector4<T>::zero = base_vector4<T>(0.0, 0.0, 0.0, 0.0);

	// vector types
	typedef base_vector2<float> vec2;
	typedef base_vector3<float> vec3;
	typedef base_vector4<float> vec4;
	typedef vec2 vector2;
	typedef vec3 vector3;
	typedef vec4 vector4;

	typedef vec2 fvec2;
	typedef vec3 fvec3;
	typedef vec4 fvec4;
	typedef vector2 fvector2;
	typedef vector3 fvector3;
	typedef vector4 fvector4;

	typedef base_vector2<double> dvec2;
	typedef base_vector3<double> dvec3;
	typedef base_vector4<double> dvec4;
	typedef dvec2 dvector2;
	typedef dvec3 dvector3;
	typedef dvec4 dvector4;

	typedef base_vector2<int> ivec2;
	typedef base_vector3<int> ivec3;
	typedef base_vector4<int> ivec4;
	typedef ivec2 ivector2;
	typedef ivec3 ivector3;
	typedef ivec4 ivector4;

	typedef base_vector2<unsigned int> uvec2;
	typedef base_vector3<unsigned int> uvec3;
	typedef base_vector4<unsigned int> uvec4;
	typedef uvec2 uvector2;
	typedef uvec3 uvector3;
	typedef uvec4 uvector4;
}