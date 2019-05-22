#pragma once

#include <cassert>
#include <cmath>
#include <cstring>
#include "matrix3.h"

namespace awesome
{
	template <typename T>
	class matrix4_t
	{
		static const matrix4_t zero;
		static const matrix4_t identity;

		// num of rows
		const std::size_t rows = 4;
		// num of columns
		const std::size_t columns = 4;
		// matrix size
		const std::size_t length = 4 * 4;

		// matrix data
		union
		{
			struct
			{
				T m00, m01, m02, m03;
				T m10, m11, m12, m13;
				T m20, m21, m22, m23;
				T m30, m31, m32, m33;
			};

			T data[4 * 4];
		};

		matrix4_t()
		{
			std::memset(data, static_cast<T>(0), length);
		}

		matrix4_t(const T t_value)
		{
			std::memset(data, t_value, length);
		}

		matrix4_t(
			const T t_m00, const T t_m01, const T t_m02, const T t_m03,
			const T t_m10, const T t_m11, const T t_m12, const T t_m13,
			const T t_m20, const T t_m21, const T t_m22, const T t_m23,
			const T t_m30, const T t_m31, const T t_m32, const T t_m33
		) :
			m00(t_m00), m01(t_m01), m02(t_m02), m03(t_m03),
			m10(t_m10), m11(t_m11), m12(t_m12), m13(t_m13),
			m20(t_m20), m21(t_m21), m22(t_m22), m23(t_m23),
			m30(t_m30), m31(t_m31), m32(t_m32), m33(t_m33)
		{

		}

		matrix4_t(const matrix4_t& t_matrix)
		{
			std::memcpy(data, t_matrix.data, length);
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
		matrix4_t transpose() const
		{
			matrix4_t MT;
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
		matrix3_t<T> minor(const unsigned int t_i, const unsigned int t_j) const
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

		matrix4_t inverse(bool& t_is_invertible) const
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
		matrix4_t adjugate() const
		{
			matrix4_t result;
			for (unsigned int j = 0; j < rows; ++j)
			{
				for (unsigned int i = 0; i < columns; ++i)
				{
					matrix3_t<T> currentMinor = minor(i, j);
					result(j, i) = static_cast<T>(std::pow(-1, i + 1)) * currentMinor.determinant();
				}
			}
			return result;
		}

		// determinant 
		T determinant() const
		{
			/* Laplace law */
			int j = 0;
			T result{};
			for (unsigned int i = 0; i < columns; ++i)
			{
				const matrix3_t<T> minor = t_m.minor(i, j);
				result += std::pow(-1, i + j) * minor.determinant();
			}
			return result;
		}

		/* Operators overloading */

		matrix4_t& operator= (const matrix4_t & t_matrix)
		{
			// check for self-assignment
			if (this == &t_matrix)
				return *this;

			std::memcpy(data, t_matrix.data, length);
			return *this;
		}

		bool operator== (const matrix4_t & t_matrix) const
		{
			return m00 == t_matrix.m00 && m01 == t_matrix.m01 && m02 == t_matrix.m02 && m03 == t_matrix.m03
				&& m01 == t_matrix.m01 && m11 == t_matrix.m11 && m12 == t_matrix.m12 && m13 == t_matrix.m13
				&& m02 == t_matrix.m02 && m21 == t_matrix.m21 && m22 == t_matrix.m22 && m23 == t_matrix.m23
				&& m03 == t_matrix.m03 && m31 == t_matrix.m31 && m32 == t_matrix.m32 && m33 == t_matrix.m33;
		}

		bool operator!= (const matrix4_t & t_matrix) const
		{
			return m00 != t_matrix.m00 || m01 != t_matrix.m01 || m02 != t_matrix.m02 || m03 != t_matrix.m03
				|| m01 != t_matrix.m01 || m11 != t_matrix.m11 || m12 != t_matrix.m12 || m13 != t_matrix.m13
				|| m02 != t_matrix.m02 || m21 != t_matrix.m21 || m22 != t_matrix.m22 || m23 != t_matrix.m23
				|| m03 != t_matrix.m03 || m31 != t_matrix.m31 || m32 != t_matrix.m32 || m33 != t_matrix.m33;
		}

		matrix4_t& operator+= (const matrix4_t & t_matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] += t_matrix.data[i];
			return *this;
		}

		matrix4_t& operator-= (const matrix4_t & t_matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] -= t_matrix.data[i];
			return *this;
		}

		matrix4_t& operator*= (const T t_scalar)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] *= t_scalar;
			return *this;
		}

		matrix4_t& operator/= (const T t_scalar)
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			return (*this) *= f;
		}

		matrix4_t operator- () const
		{
			matrix4_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = -data[i];
			return result;
		}

		matrix4_t operator+ (const matrix4_t & t_matrix) const
		{
			matrix4_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] + t_matrix.data[i];
			return result;
		}

		matrix4_t operator- (const matrix4_t & t_matrix) const
		{
			matrix4_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] - t_matrix.data[i];
			return result;
		}

		matrix4_t operator* (const T t_scalar) const
		{
			matrix4_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] * t_scalar;
			return result;
		}

		matrix4_t operator/ (const T t_scalar) const
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			return (*this) * f;
		}
	};


	// matrix types

	typedef matrix4_t<float> matrix4;
	typedef matrix4 mat4;
}