#pragma once

#include "base_vector.h"

namespace awesome
{
	template<std::size_t N, std::size_t M, class T>
	struct base_matrix
	{
		// num of rows
		const std::size_t rows = N;
		// num of columns
		const std::size_t columns = M;

		// store data into a managed array
		std::array<T, N* M> data;

		// default constructor
		base_matrix()
			: data()
		{
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_matrix(const T t_value) 
			: data()
		{
			data.fill(t_value);
		}

		// constructor with initializer list
		base_matrix(const std::initializer_list<T>& t_args) 
			: data()
		{
			unsigned int i = 0;
			for (auto it = t_args.begin(); it != t_args.end() && i < N * M; ++it) 
			{
				data[i] = *it;
				++i;
			}
		}

		// copy constructor
		base_matrix(const base_matrix<N, M, T>& t_other)
		{
			data = t_other.data;
		}

		// templated copy constructor
		template<std::size_t K, std::size_t P>
		base_matrix(const base_matrix<K, P, T>& t_other)
		{
			data.fill(T{});
			for (unsigned int j = 0; j < columns && j < P; ++j) 
			{
				for (unsigned int i = 0; i < rows && i < K; ++i) 
				{
					(*this)(i, j) = t_other(i, j);
				}
			}
		}

		// return the vector length
		std::size_t size() const 
		{
			return data.size();
		}

		// get a row
		base_vector<M, T> row(const unsigned int t_j) const 
		{
			base_vector<M, T> result;
			for (unsigned int i = 0; i < M; ++i) 
			{
				result[i] = (*this)(i, t_j);
			}
			return result;
		}

		// get a column
		base_vector<N, T> column(const unsigned int t_i) const 
		{
			base_vector<N, T> result;
			for (unsigned int j = 0; j < N; ++j) 
			{
				result[j] = (*this)(t_i, j);
			}
			return result;
		}

		// get (i,j) element
		T& operator() (const unsigned int i, const unsigned int t_j) 
		{
			return data.at(i + t_j * columns);
		}

		T operator() (const unsigned int i, const unsigned int t_j) const 
		{
			return data.at(i + t_j * columns);
		}

		// determinant 
		T determinant() const
		{
			return math4games::determinant(*this);
		}

		// sub matrix
		base_matrix<N - 1, M - 1, T> minor(const unsigned int t_x, const unsigned int t_y) const 
		{
			assert(x < columns && y < rows);
			base_matrix<N - 1, M - 1, T> result;

			for (unsigned int j = 0, _j = 0; j < rows; ++j)
			{
				if (j == t_y) continue;
				for (unsigned int i = 0, _i = 0; i < columns; ++i)
				{
					if (i == t_x) continue;
					result(_i, _j) = (*this)(i, j);
					++_i;
				}
				++_j;
			}
			return result;
		}

		// transpose matrix
		base_matrix<M, N, T> transpose() const 
		{
			base_matrix<M, N, T> MT;
			for (unsigned int j = 0; j < rows; j++) 
			{
				for (unsigned int i = 0; i < columns; i++) 
				{
					MT(i, j) = (*this)(j, i);
				}
			}
			return MT;
		}

		// inverse matrix
		base_matrix<N, M, T> inverse(bool& t_is_invertible) const 
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
		base_matrix<N, M, T> adjugate() const 
		{
			base_matrix<N, M, T> result;
			for (unsigned int j = 0; j < rows; ++j) 
			{
				for (unsigned int i = 0; i < columns; ++i) 
				{
					base_matrix<N - 1, M - 1, T> currentMinor = minor(i, j);
					result(j, i) = static_cast<T>(std::pow(-1, i + 1)) * currentMinor.determinant();
				}
			}
			return result;
		}

		/* Operators overloading */

		base_matrix<N, M, T>& operator= (const base_matrix<N, M, T> & t_other) 
		{
			// check for self-assignment
			if (this == &t_other)
				return *this;

			data = t_other.data;

			return *this;
		}

		bool operator== (const base_matrix<N, M, T> & t_other) const 
		{
			return (*this).data == t_other.data;
		}

		bool operator!= (const base_matrix<N, M, T> & t_other) const 
		{
			return !(*this == t_other);
		}

		base_matrix<N, M, T>& operator+= (const base_matrix<N, M, T> & t_other) 
		{
			for (unsigned int i = 0; i < data.size(); i++)
				data[i] += t_other.data[i];
			return *this;
		}

		base_matrix<N, M, T>& operator-= (const base_matrix<N, M, T> & t_other) 
		{
			for (unsigned int i = 0; i < data.size(); i++)
				data[i] -= t_other.data[i];
			return *this;
		}

		base_matrix<N, M, T>& operator*= (const T t_s) 
		{
			for (unsigned int i = 0; i < data.size(); i++)
				data[i] *= t_s;
			return *this;
		}

		base_matrix<N, M, T>& operator/= (const T t_s) 
		{
			assert(t_s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_s;
			return (*this) *= f;
		}

		base_matrix<N, M, T> operator- () const 
		{
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = -data[i];
			return result;
		}

		base_matrix<N, M, T> operator+ (const base_matrix<N, M, T> & t_other) const 
		{
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = data[i] + t_other.data[i];
			return result;
		}

		base_matrix<N, M, T> operator- (const base_matrix<N, M, T> & t_other) const 
		{
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = data[i] - t_other.data[i];
			return result;
		}

		base_matrix<N, M, T> operator* (const T t_s) const 
		{
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = data[i] * t_s;
			return result;
		}

		base_matrix<N, M, T> operator/ (const T t_s) const 
		{
			assert(t_s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / t_s;
			return (*this) * f;
		}
	};

	// matrix x matrix operation
	template<std::size_t N, std::size_t M, std::size_t K, typename T>
	base_matrix<N, K, T> operator* (const base_matrix<N, M, T> & t_m1, const base_matrix<M, K, T> & t_m2) 
	{
		base_matrix<N, K, T> result;
		for (unsigned int j = 0; j < N; ++j) 
		{
			for (unsigned int y = 0; y < K; ++y) 
			{
				T value{};
				for (unsigned int i = 0; i < N; ++i) 
				{
					value += t_m1(i, j) * t_m2(y, i);
				}
				result(y, j) = value;
			}
		}
		return result;
	}

	// matrix x column vector operation 
	template<std::size_t N, std::size_t M, typename T>
	base_vector<N, T> operator* (const base_matrix<N, M, T> & t_m, const base_vector<M, T> & t_v) 
	{
		base_vector<N, T> result;
		for (unsigned int j = 0; j < N; ++j) 
		{
			T value{};
			for (unsigned int i = 0; i < M; ++i) 
			{
				value += t_m(i, j) * t_v[i];
			}
			result[j] = value;
		}
		return result;
	}

	// determinant algorithm
	template<std::size_t N, std::size_t M, typename T>
	T determinant(const base_matrix<N, M, T> & t_m)
	{
		/* Laplace law */
		int j = 0;
		T result{};
		for (unsigned int i = 0; i < M; ++i) 
		{
			auto minor = t_m.minor(i, j);
			result += std::pow(-1, i + j) * determinant_algorithm(minor);
		}
		return result;
	}

	template<typename T>
	T determinant(const base_matrix<0, 0, T> & t_m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant(const base_matrix<1, 0, T> & t_m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant(const base_matrix<0, 1, T> & t_m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant(const base_matrix<1, 1, T> & t_m)
	{
		return t_m(0, 0);
	}

	template<typename T>
	T determinant(const base_matrix<2, 2, T> & t_m)
	{
		return t_m.data[0] * t_m.data[3] - (t_m.data[1] * t_m.data[2]);
	}

	template<typename T>
	T determinant(const base_matrix<3, 3, T> & t_m)
	{
		// Sarrus law
		return (t_m.data[0] * t_m.data[4] * t_m.data[8]) -
			(t_m.data[1] * t_m.data[5] * t_m.data[6]) -
			(t_m.data[2] * t_m.data[3] * t_m.data[7]);
	}
}