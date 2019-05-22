#pragma once

#include <cassert>
#include <cmath>
#include <cstring>

namespace awesome
{
	template <typename T>
	struct matrix2_t
	{
		static const matrix2_t zero;
		static const matrix2_t identity;

		// num of rows
		const std::size_t rows = 2;
		// num of columns
		const std::size_t columns = 2;
		// matrix size
		const std::size_t length = 2 * 2;

		// matrix data
		union
		{
			struct
			{
				T m00, m01;
				T m10, m11;
			};

			T data[2 * 2];
		};

		matrix2_t()
			: data()
		{
			std::memset(data, static_cast<T>(0), length * sizeof(T));
		}

		matrix2_t(const T t_value)
			: data()
		{
			std::memset(data, t_value, length * sizeof(T));
		}

		matrix2_t(
			const T t_m00, const T t_m01,
			const T t_m10, const T t_m11
		) : 
			m00(t_m00), m01(t_m01),
			m10(t_m10), m11(t_m11)
		{

		}

		matrix2_t(const matrix2_t& t_matrix)
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
			return data[i + t_j * columns];
		}

		T operator() (const unsigned int i, const unsigned int t_j) const
		{
			return data[i + t_j * columns];
		}

		// transpose matrix
		matrix2_t transpose() const
		{
			matrix2_t MT;
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
		T minor(const unsigned int t_i, const unsigned int t_j) const
		{
			assert(t_i < columns && t_j < rows);
			return (*this)(t_i == 1 ? 0 : 1, t_j == 1 ? 0 : 1);
		}

		matrix2_t inverse(bool& t_is_invertible) const
		{
			t_is_invertible = false;
			T d = determinant(*this);
			if (d != static_cast<T>(0.0)) 
			{
				t_is_invertible = true;
				return matrix2_t(
					m11, -m10,
					-m01, m00
				) / d;
			}
			return *this;
		}

		// determinant 
		T determinant() const
		{
			return m00 * m11 - m01 * m10;
		}

		/* Operators overloading */

		matrix2_t& operator= (const matrix2_t & t_matrix)
		{
			// check for self-assignment
			if (this == &t_matrix)
				return *this;

			std::memcpy(data, t_matrix.data, length * sizeof(T));
			return *this;
		}

		bool operator== (const matrix2_t & t_matrix) const
		{
			return m00 == t_matrix.m00 && m01 == t_matrix.m01
				&& m01 == t_matrix.m01 && m11 == t_matrix.m11;
		}

		bool operator!= (const matrix2_t & t_matrix) const
		{
			return m00 != t_matrix.m00 || m01 != t_matrix.m01
				|| m01 != t_matrix.m01 || m11 != t_matrix.m11;
		}

		matrix2_t& operator+= (const matrix2_t & t_matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] += t_matrix.data[i];
			return *this;
		}

		matrix2_t& operator-= (const matrix2_t & t_matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] -= t_matrix.data[i];
			return *this;
		}

		matrix2_t& operator*= (const T t_scalar)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] *= t_scalar;
			return *this;
		}

		matrix2_t& operator/= (const T t_scalar)
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			return (*this) *= f;
		}

		matrix2_t operator- () const
		{
			matrix2_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = -data[i];
			return result;
		}

		matrix2_t operator+ (const matrix2_t & t_matrix) const
		{
			matrix2_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] + t_matrix.data[i];
			return result;
		}

		matrix2_t operator- (const matrix2_t & t_matrix) const
		{
			matrix2_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] - t_matrix.data[i];
			return result;
		}

		matrix2_t operator* (const T t_scalar) const
		{
			matrix2_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] * t_scalar;
			return result;
		}

		matrix2_t operator/ (const T t_scalar) const
		{
			assert(t_scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_scalar;
			return (*this) * f;
		}
	};

	template<typename T> const matrix2_t<T> matrix2_t<T>::zero = matrix2_t<T>(0.0);
	template<typename T> const matrix2_t<T> matrix2_t<T>::identity = matrix2_t<T>(
		1.0, 0.0,
		0.0, 1.0
		);

	// matrix types

	typedef matrix2_t<float> matrix2;
	typedef matrix2 mat2;
}