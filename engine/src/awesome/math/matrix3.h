#pragma once

#include <cassert>
#include <cmath>
#include <cstring>
#include "matrix2.h"

namespace awesome
{
	template <typename T>
	struct matrix3_t
	{
		static const matrix3_t zero;
		static const matrix3_t identity;

		// num of rows
		const std::size_t rows = 3;
		// num of columns
		const std::size_t columns = 3;
		// matrix size
		const std::size_t length = 3 * 3;

		// matrix data
		union
		{
			struct
			{
				T m00, m01, m02;
				T m10, m11, m12;
				T m20, m21, m22;
			};

			T data[3 * 3];
		};

		matrix3_t()
			: data()
		{
			std::memset(data, static_cast<T>(0), length * sizeof(T));
		}

		matrix3_t(const T t_value)
			: data()
		{
			std::memset(data, t_value, length * sizeof(T));
		}

		matrix3_t(
			const T t_m00, const T t_m01, const T t_m02,
			const T t_m10, const T t_m11, const T t_m12,
			const T t_m20, const T t_m21, const T t_m22
		) : 
			m00(t_m00), m01(t_m01), m02(t_m02),
			m10(t_m10), m11(t_m11), m12(t_m12),
			m20(t_m20), m21(t_m21), m22(t_m22)
		{

		}

		matrix3_t(const matrix3_t& t_matrix)
			: data()
		{
			std::memcpy(data, t_matrix.data, length * sizeof(T));
		}

		std::size_t size() const
		{
			return length;
		}

		// get (i,j) element
		T& operator() (const unsigned int i, const unsigned int t_j)
		{
			// row major implementation
			return data.at(i + t_j * columns);
		}

		T operator() (const unsigned int i, const unsigned int t_j) const
		{
			return data.at(i + t_j * columns);
		}

		// transpose matrix
		matrix3_t transpose() const
		{
			matrix3_t MT;
			for (unsigned int j = 0; j < rows; j++)
			{
				for (unsigned int i = 0; i < columns; i++)
				{
					MT(i, j) = (*this)(j, i);
				}
			}
			return MT;
		}

		// sub matrix
		matrix2_t<T> minor(const unsigned int t_i, const unsigned int t_j) const
		{
			assert(t_i < columns && t_j < rows);
			matrix3_t result;

			for (unsigned int j = 0, _j = 0; j < rows; ++j)
			{
				if (j == t_j) continue;
				for (unsigned int i = 0, _i = 0; i < columns; ++i)
				{
					if (i == t_i) continue;
					result(_i, _j) = (*this)(i, j);
					++_i;
				}
				++_j;
			}
			return result;
		}

		matrix3_t inverse(bool& t_is_invertible) const
		{
			t_is_invertible = false;
			T d = determinant(*this);
			if (d != static_cast<T>(0.0)) {
				t_is_invertible = true;
				return adjugate() / d;
			}
			return *this;
		}

		// adjugate matrix
		matrix3_t adjugate() const
		{
			matrix3_t result;
			for (unsigned int j = 0; j < rows; ++j)
			{
				for (unsigned int i = 0; i < columns; ++i)
				{
					matrix2_t<T> currentMinor = minor(i, j);
					result(j, i) = static_cast<T>(std::pow(-1, i + 1)) * currentMinor.determinant();
				}
			}
			return result;
		}

		// determinant 
		T determinant() const
		{
			// Sarrus law
			return (m00 * m11 * m22) -
				(m01 * m12 * m20) -
				(m02 * m10 * m21);
		}

		/* Operators overloading */

		matrix3_t& operator= (const matrix3_t & t_matrix)
		{
			// check for self-assignment
			if (this == &t_matrix)
				return *this;

			std::memcpy(data, t_matrix.data, length * sizeof(T));
			return *this;
		}

		bool operator== (const matrix3_t & t_matrix) const
		{
			return m00 == t_matrix.m00 && m01 == t_matrix.m01 && m02 == t_matrix.m02
				&& m01 == t_matrix.m01 && m11 == t_matrix.m11 && m12 == t_matrix.m12
				&& m02 == t_matrix.m02 && m21 == t_matrix.m21 && m22 == t_matrix.m22;
		}

		bool operator!= (const matrix3_t & t_matrix) const
		{
			return m00 != t_matrix.m00 || m01 != t_matrix.m01 || m02 != t_matrix.m02
				|| m01 != t_matrix.m01 || m11 != t_matrix.m11 || m12 != t_matrix.m12
				|| m02 != t_matrix.m02 || m21 != t_matrix.m21 || m22 != t_matrix.m22;
		}

		matrix3_t& operator+= (const matrix3_t & t_matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] += t_matrix.data[i];
			return *this;
		}

		matrix3_t& operator-= (const matrix3_t & t_matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] -= t_matrix.data[i];
			return *this;
		}

		matrix3_t& operator*= (const T t_scalar)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] *= t_scalar;
			return *this;
		}

		matrix3_t& operator/= (const T t_scalar)
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			return (*this) *= f;
		}

		matrix3_t operator- () const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = -data[i];
			return result;
		}

		matrix3_t operator+ (const matrix3_t & t_matrix) const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] + t_matrix.data[i];
			return result;
		}

		matrix3_t operator- (const matrix3_t & t_matrix) const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] - t_matrix.data[i];
			return result;
		}

		matrix3_t operator* (const T t_scalar) const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] * t_scalar;
			return result;
		}

		matrix3_t operator/ (const T t_scalar) const
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			return (*this) * f;
		}
	};

	template<typename T> const matrix3_t<T> matrix3_t<T>::zero = matrix3_t<T>(0.0);
	template<typename T> const matrix3_t<T> matrix3_t<T>::identity = matrix3_t<T>(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
		);

	// matrix types

	typedef matrix3_t<float> matrix3;
	typedef matrix3 mat3;
}