#pragma once

#include "vector.h"

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
		std::array<T, N * M> data;

		// default constructor
		base_matrix() {
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_matrix(const T value) {
			data.fill(value);
		}

		// constructor with initializer list
		base_matrix(const std::initializer_list<T>& args) {
			unsigned int i = 0;
			for (auto it = args.begin(); it != args.end() && i < N * M; ++it) {
				data[i] = *it;
				++i;
			}
		}

		// copy constructor
		base_matrix(const base_matrix<N, M, T>& other)
		{
			data = other.data;
		}

		// templated copy constructor
		template<std::size_t K, std::size_t P>
		base_matrix(const base_matrix<K, P, T>& other)
		{
			data.fill(T{});
			for (unsigned int j = 0; j < columns && j < P; ++j) {
				for (unsigned int i = 0; i < rows && i < K; ++i) {
					(*this)(i, j) = other(i, j);
				}
			}
		}

		// return the vector length
		std::size_t size() const {
			return data.size();
		}

		// get a row
		base_vector<M, T> row(const unsigned int j) const {
			base_vector<M, T> result;
			for (unsigned int i = 0; i < M; ++i) {
				result[i] = (*this)(i, j);
			}
			return result;
		}

		// get a column
		base_vector<N, T> column(const unsigned int i) const {
			base_vector<N, T> result;
			for (unsigned int j = 0; j < N; ++j) {
				result[j] = (*this)(i, j);
			}
			return result;
		}

		// get (i,j) element
		T& operator() (const unsigned int i, const unsigned int j) {
			return data.at(i + j * columns);
		}

		T operator() (const unsigned int i, const unsigned int j) const {
			return data.at(i + j * columns);
		}
		
		// determinant 
		T determinant() const
		{
			return math4games::determinant(*this);
		}

		// sub matrix
		base_matrix<N - 1, M - 1, T> minor(const unsigned int x, const unsigned int y) const {
			assert(x < columns && y < rows);
			base_matrix<N - 1, M - 1, T> result;

			for (unsigned int j = 0, _j = 0; j < rows; ++j)
			{
				if (j == y) continue;
				for (unsigned int i = 0, _i = 0; i < columns; ++i)
				{
					if (i == x) continue;
					result(_i, _j) = (*this)(i, j);
					++_i;
				}
				++_j;
			}
			return result;
		}

		// transpose matrix
		base_matrix<M, N, T> transpose() const {
			base_matrix<M, N, T> MT;
			for (unsigned int j = 0; j < rows; j++) {
				for (unsigned int i = 0; i < columns; i++) {
					MT(i, j) = (*this)(j, i);
				}
			}
			return MT;
		}

		// inverse matrix
		base_matrix<N, M, T> inverse(bool& invertible) const {
			invertible = false;
			T d = determinant(*this);
			if (d != static_cast<T>(0.0)) {
				invertible = true;
				return adjugate() / d;
			}
			return *this;
		}

		// adjugate matrix
		base_matrix<N, M, T> adjugate() const {
			base_matrix<N, M, T> result;
			for (unsigned int j = 0; j < rows; ++j) {
				for (unsigned int i = 0; i < columns; ++i) {
					base_matrix<N - 1, M - 1, T> currentMinor = minor(i, j);
					result(j, i) = static_cast<T>(std::pow(-1, i + 1))*currentMinor.determinant();
				}
			}
			return result;
		}

		/* Operators overloading */

		base_matrix<N, M, T>& operator= (const base_matrix<N, M, T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			data = other.data;

			return *this;
		}

		bool operator== (const base_matrix<N, M, T>& other) const {
			return (*this).data == other.data;
		}

		bool operator!= (const base_matrix<N, M, T>& other) const {
			return !(*this == other);
		}

		base_matrix<N, M, T>& operator+= (const base_matrix<N, M, T>& other) {
			for (unsigned int i = 0; i < data.size(); i++)
				data[i] += other.data[i];
			return *this;
		}

		base_matrix<N, M, T>& operator-= (const base_matrix<N, M, T>& other) {
			for (unsigned int i = 0; i < data.size(); i++)
				data[i] -= other.data[i];
			return *this;
		}

		base_matrix<N, M, T>& operator*= (const T s) {
			for (unsigned int i = 0; i < data.size(); i++)
				data[i] *= s;
			return *this;
		}

		base_matrix<N, M, T>& operator/= (const T s) {
			assert(s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / s;
			return (*this) *= f;
		}

		base_matrix<N, M, T> operator- () const {
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = -data[i];
			return result;
		}

		base_matrix<N, M, T> operator+ (const base_matrix<N, M, T>& other) const {
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = data[i] + other.data[i];
			return result;
		}

		base_matrix<N, M, T> operator- (const base_matrix<N, M, T>& other) const {
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = data[i] - other.data[i];
			return result;
		}

		base_matrix<N, M, T> operator* (const T s) const {
			base_matrix<N, M, T> result;
			for (unsigned int i = 0; i < data.size(); i++)
				result.data[i] = data[i] * s;
			return result;
		}

		base_matrix<N, M, T> operator/ (const T s) const {
			assert(s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / s;
			return (*this) * f;
		}
	};

	// matrix x matrix operation
	template<std::size_t N, std::size_t M, std::size_t K, typename T>
	base_matrix<N, K, T> operator* (const base_matrix<N, M, T>& m1, const base_matrix<M, K, T>& m2) {
		base_matrix<N, K, T> result;
		for (unsigned int j = 0; j < N; ++j) {
			for (unsigned int y = 0; y < K; ++y) {
				T value{};
				for (unsigned int i = 0; i < N; ++i) {
					value += m1(i, j) * m2(y, i);
				}
				result(y, j) = value;
			}
		}
		return result;
	}

	// matrix x column vector operation 
	template<std::size_t N, std::size_t M, typename T>
	base_vector<N, T> operator* (const base_matrix<N, M, T>& m, const base_vector<M, T>& v) {
		base_vector<N, T> result;
		for (unsigned int j = 0; j < N; ++j) {
			T value{};
			for (unsigned int i = 0; i < M; ++i) {
				value += m(i, j) * v[i];
			}
			result[j] = value;
		}
		return result;
	}

	// determinant algorithm
	template<std::size_t N, std::size_t M, typename T>
	T determinant(const base_matrix<N, M, T>& m)
	{
		/* Laplace law */
		int j = 0;
		T result{};
		for (unsigned int i = 0; i < M; ++i) {
			auto minor = m.minor(i, j);
			result += std::pow(-1, i + j)*determinant_algorithm(minor);
		}
		return result;
	}

	template<typename T>
	T determinant(const base_matrix<0, 0, T>& m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant(const base_matrix<1, 0, T>& m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant(const base_matrix<0, 1, T>& m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant(const base_matrix<1, 1, T>& m)
	{
		return m(0, 0);
	}

	template<typename T>
	T determinant(const base_matrix<2, 2, T>& m)
	{
		return m.data[0] * m.data[3] - (m.data[1] * m.data[2]);
	}

	template<typename T>
	T determinant(const base_matrix<3, 3, T>& m)
	{
		// Sarrus law
		return (m.data[0] * m.data[4] * m.data[8]) -
			(m.data[1] * m.data[5] * m.data[6]) -
			(m.data[2] * m.data[3] * m.data[7]);
	}

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

		base_matrix2() :base_matrix<2, 2, T>() {}

		base_matrix2& operator= (const base_matrix2& other) {
			base_matrix<2, 2, T>::data = other.data;
			return (*this);
		}

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

		base_matrix3() :base_matrix<3, 3, T>() {}

		base_matrix3& operator= (const base_matrix3& other) {
			base_matrix<3, 3, T>::data = other.data;
			return (*this);
		}

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

		base_matrix4() :base_matrix<4, 4, T>() {}

		base_matrix4& operator= (const base_matrix4& other) {
			base_matrix<4, 4, T>::data = other.data;
			return (*this);
		}

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
