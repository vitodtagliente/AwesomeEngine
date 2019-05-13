#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>

namespace awesome
{
	template<std::size_t N, typename T>
	struct base_vector
	{
		// vector size
		const std::size_t length = N;

		// store data into a managed array
		std::array<T, N> data;

		// default constructor
		base_vector() {
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_vector(const T value) {
			data.fill(value);
		}

		// construct with initialzie list
		base_vector(const std::initializer_list<T>& args) {
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = args.begin(); it != args.end() && i < length; ++it) {
				data[i] = *it;
				++i;
			}
		}

		// copy constructor
		base_vector(const base_vector<N, T>& other)
		{
			data = other.data;
		}

		// templated copy constructor
		template<std::size_t M>
		base_vector(const base_vector<M, T>& other)
		{
			data.fill(T{});
			unsigned int i = 0;
			for (auto it = other.data.begin(); it != other.data.end() && i < length; ++it)
			{
				data[i] = *it;
				++i;
			}
		}

		// return the vector length
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

		// compute the magnitude
		// magnitude = x1 * x1 + x2 * x2 + ... + xn * xn
		T magnitude() const {
			T result = {};
			for (unsigned int i = 0; i < length; ++i)
				result += data[i] * data[i];
			return static_cast<T>(sqrt(result));
		}

		// compute the distance between another vector
		T distance(const base_vector<N, T> & other) const {
			return (*this - other).magnitude();
		}

		// dot product
		T dot(const base_vector<N, T> & other) const {
			return (*this)* other;
		}

		// normalize the vector
		base_vector<N, T> normalize() {
			return (*this *= (static_cast<T>(1.0) / magnitude()));
		}

		base_vector<N, T> project(const base_vector<N, T> & v) {
			T d = v * v;
			assert(d != static_cast<T>(0.0));
			return v * ((*this * v) / d);
		}

		base_vector<N, T> reject(const base_vector<N, T> & v) {
			T d = v * v;
			assert(d != static_cast<T>(0.0));
			return (*this - v) * ((*this * v) / d);
		}

		// Operators overloading 

		base_vector<N, T> & operator= (const base_vector<N, T> & other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			// copy 
			data = other.data;
			return *this;
		}

		bool operator== (const base_vector<N, T> & other) const {
			return (*this).data == other.data;
		}

		bool operator!= (const base_vector<N, T> & other) const {
			return !(*this == other);
		}

		base_vector<N, T>& operator+= (const base_vector<N, T> & other) {
			for (unsigned int i = 0; i < length; i++)
				data[i] += other[i];
			return *this;
		}

		base_vector<N, T>& operator-= (const base_vector<N, T> & other) {
			for (unsigned int i = 0; i < length; i++)
				data[i] -= other[i];
			return *this;
		}

		base_vector<N, T>& operator*= (const T s) {
			for (unsigned int i = 0; i < length; i++)
				data[i] *= s;
			return *this;
		}

		base_vector<N, T>& operator/= (const T s) {
			assert(s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / s;
			for (unsigned int i = 0; i < length; i++)
				data[i] *= f;
			return *this;
		}

		base_vector<N, T> operator- () const {
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = -data[i];
			return v;
		}

		base_vector<N, T> operator+ (const base_vector<N, T> & w) const {
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] + w[i];
			return v;
		}

		base_vector<N, T> operator- (const base_vector<N, T> & w) const {
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] - w[i];
			return v;
		}

		base_vector<N, T> operator* (const T s) const {
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] * s;
			return v;
		}

		base_vector<N, T> operator/ (const T s) const {
			assert(s != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / s;
			base_vector<N, T> v;
			for (unsigned int i = 0; i < length; i++)
				v[i] = data[i] * f;
			return v;
		}

		// dot product 
		T operator*(const base_vector<N, T> & v) const {
			T dot{};
			for (unsigned int i = 0; i < length; i++)
				dot += data[i] * v[i];
			return dot;
		}
	};

	template<std::size_t N, class T>
	inline base_vector<N, T> operator* (const T s, const base_vector<N, T> & v) {
		base_vector<N, T> w;
		for (unsigned int i = 0; i < N; i++)
			w[i] = v[i] * s;
		return w;
	}

	// undefined order zero vector
	template<typename T>
	struct base_vector<0, T>;

	// order 2 vector
	template<typename T>
	struct base_vector2 : public base_vector<2, T>
	{
		// inherits base class constructors
		using base_vector<2, T>::base_vector;

		base_vector2() :base_vector<2, T>() {}

		T& x = base_vector<2, T>::data[0];
		T& y = base_vector<2, T>::data[1];

		base_vector2(const T _x, const T _y)
		{
			base_vector<2, T>::data[0] = _x;
			base_vector<2, T>::data[1] = _y;
		}

		base_vector2& operator= (const base_vector2& other) {
			base_vector<2, T>::data = other.data;
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

		base_vector3() :base_vector<3, T>() {}

		T& x = base_vector<3, T>::data[0];
		T& y = base_vector<3, T>::data[1];
		T& z = base_vector<3, T>::data[2];

		base_vector3(const T _x, const T _y, const T _z) {
			base_vector<3, T>::data[0] = _x;
			base_vector<3, T>::data[1] = _y;
			base_vector<3, T>::data[2] = _z;
		}

		//cross product
		base_vector3<T> cross(const base_vector3<T>& v) const {
			return base_vector3<T>(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
				);
		}

		// scalar triple product
		float triple(const  base_vector3<T> & v, const  base_vector3<T> & w) const {
			return ((*this).cross(v))* w;
		}

		base_vector3& operator= (const base_vector3 & other) {
			base_vector<3, T>::data = other.data;
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

		base_vector4() :base_vector<4, T>() {}

		T& x = base_vector<4, T>::data[0];
		T& y = base_vector<4, T>::data[1];
		T& z = base_vector<4, T>::data[2];
		T& w = base_vector<4, T>::data[3];

		base_vector4(const T _x, const T _y, const T _z, const T _w) {
			base_vector<4, T>::data[0] = _x;
			base_vector<4, T>::data[1] = _y;
			base_vector<4, T>::data[2] = _z;
			base_vector<4, T>::data[3] = _w;
		}

		base_vector4& operator= (const base_vector4& other) {
			base_vector<4, T>::data = other.data;
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