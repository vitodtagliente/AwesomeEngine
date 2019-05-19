#pragma once

#include "base_matrix.h"

namespace awesome
{
	// undefined order zero matrix
	template<typename T>
	struct base_matrix<0, 0, T>;

	template<typename T>
	struct base_matrix<1, 0, T>;

	template<typename T>
	struct base_matrix<0, 1, T>;

	// order one matrix
	template<typename T>
	struct base_matrix1 : public base_matrix<1, 1, T>
	{
		// inherits base class constructors
		using base_matrix<1, 1, T>::base_matrix;
	};

	// order 2 matrix
	template<typename T>
	struct base_matrix2 : public base_matrix<2, 2, T>
	{
		// inherits base class constructors
		using base_matrix<2, 2, T>::base_matrix;

		base_matrix2() 
			: base_matrix<2, 2, T>() 
		{}

		static const base_matrix2<T> zero;
		static const base_matrix2<T> identity;
	};

	template<typename T> const base_matrix2<T> base_matrix2<T>::zero = base_matrix2<T>(0.0);
	template<typename T> const base_matrix2<T> base_matrix2<T>::identity = base_matrix2<T>({ 1.0, 0.0, 0.0, 1.0 });

	// order 3 matrix
	template<typename T>
	struct base_matrix3 : public base_matrix<3, 3, T>
	{
		// inherits base class constructors
		using base_matrix<3, 3, T>::base_matrix;

		base_matrix3() 
			: base_matrix<3, 3, T>() 
		{}

		static const base_matrix3<T> zero;
		static const base_matrix3<T> identity;
	};

	template<typename T> const base_matrix3<T> base_matrix3<T>::zero = base_matrix3<T>(0.0);
	template<typename T> const base_matrix3<T> base_matrix3<T>::identity = base_matrix3<T>
	(
		{ 
			1.0, 0.0, 0.0, 
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		}
	);

	// order 4 matrix
	template<typename T>
	struct base_matrix4 : public base_matrix<4, 4, T>
	{
		// inherits base class constructors
		using base_matrix<4, 4, T>::base_matrix;

		base_matrix4() 
			: base_matrix<4, 4, T>() 
		{}

		static const base_matrix4<T> zero;
		static const base_matrix4<T> identity;
	};

	template<typename T> const base_matrix4<T> base_matrix4<T>::zero = base_matrix4<T>(0.0);
	template<typename T> const base_matrix4<T> base_matrix4<T>::identity = base_matrix4<T>
	(
		{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		}
	);

	// matrix types
	typedef base_matrix2<float> matrix2;
	typedef base_matrix3<float> matrix3;
	typedef base_matrix4<float> matrix4;
	typedef matrix2 mat2;
	typedef matrix3 mat3;
	typedef matrix4 mat4;

	typedef matrix2 fmatrix2;
	typedef matrix3 fmatrix3;
	typedef matrix4 fmatrix4;
	typedef mat2 fmat2;
	typedef mat3 fmat3;
	typedef mat4 fmat4;

	typedef base_matrix2<double> dmatrix2;
	typedef base_matrix3<double> dmatrix3;
	typedef base_matrix4<double> dmatrix4;
	typedef dmatrix2 dmat2;
	typedef dmatrix3 dmat3;
	typedef dmatrix4 dmat4;

	typedef base_matrix2<int> imatrix2;
	typedef base_matrix3<int> imatrix3;
	typedef base_matrix4<int> imatrix4;
	typedef imatrix2 imat2;
	typedef imatrix3 imat3;
	typedef imatrix4 imat4;

	typedef base_matrix2<unsigned int> umatrix2;
	typedef base_matrix3<unsigned int> umatrix3;
	typedef base_matrix4<unsigned int> umatrix4;
	typedef umatrix2 umat2;
	typedef umatrix3 umat3;
	typedef umatrix4 umat4;
};
