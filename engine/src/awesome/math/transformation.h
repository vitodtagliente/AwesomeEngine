#pragma once

#include "matrix.h"
#include "point.h"
#include "quaternion.h"
#include "vector.h"

namespace awesome
{
	// identity matrix
	template <std::size_t N, typename T>
	base_matrix<N, N, T> identity() 
	{
		base_matrix<N, N, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = static_cast<T>(1.0);
		return m;
	}

	// point to vector
	template <std::size_t N, typename T>
	base_vector<N + 1, T> vector(const base_point<N, T>& t_p) 
	{
		base_vector<N + 1, T> v;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = t_p[i];
		v[N] = static_cast<T>(1.0);
		return v;
	}

	// vector to point
	template <std::size_t N, typename T>
	base_point<N - 1, T> point(const base_vector<N, T>& t_v) 
	{
		static_assert(N > 1, "invalid N");
		base_point<N - 1, T> p;
		for (unsigned int i = 0; i < N - 1; ++i)
			n[i] = t_v[i];
		return p;
	}

	// point - point operation
	template <std::size_t N, typename T>
	base_vector<N, T> operator- (const base_point<N, T>& t_p1, const base_point<N, T>& t_p2) 
	{
		base_vector<N, T> v;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = t_p1[i] - t_p2[i];
		return v;
	}

	// point + vector operation
	template <std::size_t N, typename T>
	base_point<N, T> operator+ (const base_point<N, T>& t_p, const base_vector<N, T>& t_v) 
	{
		base_point<N, T> new_point;
		for (unsigned int i = 0; i < N; ++i)
			new_point[i] = t_p[i] + t_v[i];
		return new_point;
	}

	// point + vector operation
	template <std::size_t N, typename T>
	base_point<N, T> operator+ (const base_vector<N, T>& t_v, const base_point<N, T>& t_p) 
	{
		return t_p + t_v;
	}

	// translation operation
	template <std::size_t N, typename T>
	base_matrix<N + 1, N + 1, T> translate(const base_vector<N, T>& t_v) 
	{
		base_matrix<N + 1, N + 1, T> m = identity<N + 1, T>();
		for (unsigned int j = 0; j < N; ++j)
			m(N, j) = t_v[j];
		m(N, N) = static_cast<T>(1.0);
		return m;
	}

	template <std::size_t N, typename T>
	void translate(base_matrix<N + 1, N + 1, T>& t_m, const base_vector<N, T>& t_v) 
	{
		for (unsigned int j = 0; j < N; ++j)
			t_m(N, j) += t_v[j];
	}

	// rotate operation
	template <std::size_t N, typename T>
	base_matrix<N, N, T> rotate_x(const float t_theta) 
	{
		const float rad = radians(t_theta);
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
	base_matrix<N, N, T> rotate_y(const float t_theta) 
	{
		const float rad = radians(t_theta);
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
	base_matrix<N, N, T> rotate_z(const float t_theta) 
	{
		const float rad = radians(t_theta);
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
	base_matrix<4, 4, T> rotate(const base_vector<3, T>& t_v, const float t_theta) 
	{
		const float rad = radians(t_theta);
		const float c = std::cos(rad);
		const float s = std::sin(rad);
		const float c1 = 1 - c;

		base_matrix<4, 4, T> m({
			std::pow(t_v.x,2)*c1 + c,	t_v.x*t_v.y*c1 - t_v.z*s,	t_v.x*t_v.normalize*c1 + t_v.y*s,	0,
			t_v.x*t_v.y*c1 + t_v.z*s,	std::pow(t_v.y,2)*c1 + c,	t_v.y*t_v.z*c1 - t_v.x*s,			0,
			t_v.x*t_v.y*c1 - t_v.y*s,	t_v.y*t_v.z*c1 - t_v.x*s,	std::pow(t_v.z,2)*c1 + c,			0,
			0,							0,							0,									1
		});
		return m;
	}

	// scale operation
	template <std::size_t N, typename T>
	base_matrix<N + 1, N + 1, T> scale(const base_vector<N, T>& t_v) 
	{
		base_matrix<N + 1, N + 1, T> m;
		for (unsigned int i = 0; i < N; ++i)
			m(i, i) = t_v[i];
		m(N, N) = static_cast<T>(1.0);
		return m;
	}

	template <std::size_t N, typename T>
	void scale(base_matrix<N + 1, N + 1, T>& t_m, const base_vector<N, T>& t_v) 
	{
		for (unsigned int i = 0; i < N; ++i) 
			t_m(i, i) *= t_v[i];
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
	base_matrix<4, 4, float> orthographic(
		const float t_left, 
		const float t_right,
		const float t_bottom, 
		const float t_top,
		const float t_near_plane, 
		const float t_far_plane);
	
	// perspective projection
	base_matrix<4, 4, float> perspective(
		const float t_fov, 
		const float t_aspect,
		const float t_near_plane, 
		const float t_far_plane);
}
