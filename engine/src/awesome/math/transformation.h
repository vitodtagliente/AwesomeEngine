#pragma once

#include "matrix.h"
#include "point.h"
#include "quaternion.h"
#include "vector.h"

namespace awesome
{
	// identity matrix
	template <std::size_t N, typename T>
	base_matrix<N, N, T> identity() {
		base_matrix<N, N, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = static_cast<T>(1.0);
		return m;
	}

	// point to vector
	template <std::size_t N, typename T>
	base_vector<N + 1, T> vector(const base_point<N, T>& p) {
		base_vector<N + 1, T> v;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = p[i];
		v[N] = static_cast<T>(1.0);
		return v;
	}

	// vector to point
	template <std::size_t N, typename T>
	base_point<N - 1, T> point(const base_vector<N, T>& v) {
		static_assert(N > 1, "invalid N");
		base_point<N - 1, T> p;
		for (unsigned int i = 0; i < N - 1; ++i)
			n[i] = v[i];
		return p;
	}

	// point - point operation
	template <std::size_t N, typename T>
	base_vector<N, T> operator- (const base_point<N, T>& p1, const base_point<N, T>& p2) {
		base_vector<N, T> v;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = p1[i] - p2[i];
		return v;
	}

	// point + vector operation
	template <std::size_t N, typename T>
	base_point<N, T> operator+ (const base_point<N, T>& p, const base_vector<N, T>& v) {
		base_point<N, T> new_point;
		for (unsigned int i = 0; i < N; ++i)
			new_point[i] = p[i] + v[i];
		return new_point;
	}

	// point + vector operation
	template <std::size_t N, typename T>
	base_point<N, T> operator+ (const base_vector<N, T>& v, const base_point<N, T>& p) {
		return p + v;
	}

	// translation operation
	template <std::size_t N, typename T>
	base_matrix<N + 1, N + 1, T> translate(const base_vector<N, T>& v) {
		base_matrix<N + 1, N + 1, T> m = identity<N + 1, T>();
		for (unsigned int j = 0; j < N; ++j)
			m(N, j) = v[j];
		m(N, N) = static_cast<T>(1.0);
		return m;
	}

	template <std::size_t N, typename T>
	void translate(base_matrix<N + 1, N + 1, T>& m, const base_vector<N, T>& v) {
		for (unsigned int j = 0; j < N; ++j)
			m(N, j) += v[j];
	}

	// rotate operation
	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_x(const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(1, 1) = c;
		m(2, 1) = s;
		m(1, 2) = -s;
		m(2, 2) = c;
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_y(const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = c;
		m(2, 0) = -s;
		m(0, 2) = s;
		m(2, 2) = c;
		return m;
	}

	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_z(const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);

		base_matrix<N, N, T> m = identity<N, T>();
		m(0, 0) = c;
		m(1, 0) = s;
		m(0, 1) = -s;
		m(1, 1) = c;
		return m;
	}

	// 3D rotation about an arbitrary axis v by an angle theta
	template <typename T>
	base_matrix<4, 4, T> rotate(const base_vector<3, T>& v, const float theta) {
		const float rad = radians(theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);
		const float c1 = 1 - c;

		base_matrix<4, 4, T> m({
			std::pow(v.x,2)*c1 + c,	v.x*v.y*c1 - v.z*s,		v.x*v.normalize*c1 + v.y*s,		0,
			v.x*v.y*c1 + v.z*s,		std::pow(v.y,2)*c1 + c, v.y*v.z*c1 - v.x*s,				0,
			v.x*v.y*c1 - v.y*s,		v.y*v.z*c1 - v.x*s,		std::pow(v.z,2)*c1 + c,			0,
			0,						0,						0,								1
		});
		return m;
	}

	// scale operation
	template <std::size_t N, typename T>
	base_matrix<N + 1, N + 1, T> scale(const base_vector<N, T>& v) {
		base_matrix<N + 1, N + 1, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = v[i];
		m(N, N) = static_cast<T>(1.0);
		return m;
	}

	template <std::size_t N, typename T>
	void scale(base_matrix<N + 1, N + 1, T>& m, const base_vector<N, T>& v) {
		for (unsigned int i = 0; i < N; ++i) 
			m(i, i) *= v[i];
	}

	/*
	// transform matrix
	template <std::size_t N, typename T>
	base_matrix<N + 1, N + 1, T> transform(const base_vector<N, T>& position,
		const base_vector<N, T>& rotation, const base_vector<N, T>& scale) {
		base_matrix<N + 1, N + 1, T> m = identity<N + 1, T>();
		// translation
		translate(m, position);
		// rotation
		// TODO
		// scaling
		math4games::scale(m, scale);
		return m;
	}	

	template <typename T>
	base_matrix<3, 3, T> transform(const base_vector<2, T>& position,
		const base_vector<2, T>& rotation, const base_vector<2, T>& scale) {
		base_matrix<3, 3, T> m = identity<3, T>();
		// translation
		translate(m, position);
		// rotation
		const float theta = degrees(std::acosf(rotation.x / rotation.magnitude()));
		m = m * rotate_z(theta);
		// scaling
		math4games::scale(m, scale);
		return m;
	}
	*/
	
	// orthograpic pojection
	base_matrix<4, 4, float> orthographic(const float left, const float right, 
		const float bottom, const float top, 
		const float near_plane, const float far_plane) 
	{
		base_matrix<4, 4, float> m = identity<4, float>();
		
		m(0, 0) = 2.0f / (right - left);        
        m(1, 1) = 2.0f / (top - bottom);
        m(2, 2) = -2.0f / (far_plane - near_plane);

        m(3, 0) = -(right + left) / (right - left);
        m(3, 1) = -(top + bottom) / (top - bottom);
        m(3, 2) = -(far_plane + near_plane) / (far_plane - near_plane);
		
		return m;
	}
	
	// perspective projection
    base_matrix<4, 4, float> perspective(const float fov, const float aspect, const float near_plane, const float far_plane)
    {
        base_matrix<4, 4, float> m(0.0f);

        float top    = near_plane * std::tan(fov / 2.0f);
        float bottom = -top;
        float right  =  top * aspect;
        float left   = -top * aspect;

        m(0, 0) = (2.0f * near_plane) / (right - left);
        m(1, 1) = (2.0f * near_plane) / (top - bottom);
        m(2, 2) = -(far_plane + near_plane) / (far_plane - near_plane); 
		
        m(2, 3) = -1.0f;
        m(3, 2) = -(2.0f * near_plane*far_plane) / (far_plane - near_plane); 
        

        return m;
    }
}
