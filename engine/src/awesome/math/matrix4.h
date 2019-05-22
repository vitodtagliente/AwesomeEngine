#pragma once

#include <cassert>
#include <cmath>
#include <cstring>
#include "matrix3.h"
#include "vector4.h"
#include "vector3.h"

namespace awesome
{
	template <typename T>
	struct matrix4_t
	{
		static const matrix4_t zero;
		static const matrix4_t identity;

		// num of rows
		const std::size_t rows = 4;
		// num of columns
		const std::size_t columns = 4;
		// matrix size
		const std::size_t length = rows * columns;

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
			: data()
		{
			std::memset(data, static_cast<int>(0), length * sizeof(T));
		}

		matrix4_t(const T t_value)
			: data()
		{
			std::memset(data, t_value, length * sizeof(T));
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

		// orthograpic pojection
		static matrix4_t orthographic(
			const float t_left,
			const float t_right,
			const float t_bottom,
			const float t_top,
			const float t_near_plane,
			const float t_far_plane);

		// perspective projection
		static matrix4_t perspective(
			const float t_fov,
			const float t_aspect,
			const float t_near_plane,
			const float t_far_plane);

		// translation matrix
		static matrix4_t translate(const vector3_t<T>& t_vector);
		static matrix4_t translate(const vector4_t<T>& t_vector);

		/* Operators overloading */

		matrix4_t& operator= (const matrix4_t & t_matrix)
		{
			// check for self-assignment
			if (this == &t_matrix)
				return *this;

			std::memcpy(data, t_matrix.data, length * sizeof(T));
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

		matrix4_t operator* (const matrix4_t& t_matrix) const
		{
			matrix4_t result;
			for (unsigned int j = 0; j < rows; ++j)
			{
				for (unsigned int y = 0; y < columns; ++y)
				{
					T value{};
					for (unsigned int i = 0; i < rows; ++i)
					{
						value += (*this)(i, j) * t_matrix(y, i);
					}
					result(y, j) = value;
				}
			}
			return result;
		}

		vector4_t<T> operator* (const vector4_t<T>& t_vector) const
		{
			vector4_t<T> result;
			for (unsigned int j = 0; j < rows; ++j)
			{
				T value{};
				for (unsigned int i = 0; i < columns; ++i)
				{
					value += (*this)(i, j) * t_vector[i];
				}
				result[j] = value;
			}
			return result;
		}
	};

	template<typename T>
	inline matrix4_t<T> matrix4_t<T>::orthographic(const float t_left, const float t_right, const float t_bottom, const float t_top, const float t_near_plane, const float t_far_plane)
	{
		matrix4_t<T> m = matrix4_t<T>::identity;

		const T two = static_cast<T>(2.0);

		m.m00 = two / (t_right - t_left);
		m.m11 = two / (t_top - t_bottom);
		m.m22 = -two / (t_far_plane - t_near_plane);

		m.m30 = -(t_right + t_left) / (t_right - t_left);
		m.m31 = -(t_top + t_bottom) / (t_top - t_bottom);
		m.m32 = -(t_far_plane + t_near_plane) / (t_far_plane - t_near_plane);

		return m;
	}
	
	template<typename T>
	inline matrix4_t<T> matrix4_t<T>::perspective(const float t_fov, const float t_aspect, const float t_near_plane, const float t_far_plane)
	{
		matrix4_t<T> m = matrix4_t<T>::identity;

		const T two = static_cast<T>(2.0);

		float top = t_near_plane * std::tan(t_fov / two);
		float bottom = -top;
		float right = top * t_aspect;
		float left = -top * t_aspect;

		m.m00 = (two * t_near_plane) / (right - left);
		m.m11 = (two * t_near_plane) / (top - bottom);
		m.m22 = -(t_far_plane + t_near_plane) / (t_far_plane - t_near_plane);
		 
		m.m23 = -static_cast<T>(1.0);
		m.m32 = -(2.0f * t_near_plane * t_far_plane) / (t_far_plane - t_near_plane);

		return m;
	}

	template<typename T>
	inline matrix4_t<T> matrix4_t<T>::translate(const vector3_t<T>& t_vector)
	{
		return matrix4_t();
	}

	template<typename T>
	inline matrix4_t<T> matrix4_t<T>::translate(const vector4_t<T>& t_vector)
	{
		return matrix4_t();
	}

	template<typename T> const matrix4_t<T> matrix4_t<T>::zero = matrix4_t<T>(0.0);
	template<typename T> const matrix4_t<T> matrix4_t<T>::identity = matrix4_t<T>(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		);

	// matrix types

	typedef matrix4_t<float> matrix4;
	typedef matrix4 mat4;

}