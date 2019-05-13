#pragma once

#include <cmath>
#include "common.h"
#include "vector.h"

namespace awesome
{
	struct quaternion
	{
		// vector part
		vector3 v;

		// scalar part
		float w;

		quaternion() {
			w = 0.0f;
		}

		quaternion(const vector3& vector, const float scalar = 0.0f) {
			const float half_angle = 0.5f * radians(scalar);
			const float s = std::sin(half_angle);
			v[0] = v.x * s;
			v[1] = v.y * s;
			v[2] = v.z * s;
			w = std::cos(half_angle);
		}

		quaternion(const float x, const float y, const float z, const float _w = 0.0f) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			w = _w;
		}

		// operator overloading

		quaternion operator- () {
			return quaternion(-v, -w);
		}

		quaternion operator+ (const quaternion& q) const {
			return quaternion(v + q.v, w + q.w);
		}

		quaternion& operator+= (const quaternion& q) {
			v += q.v;
			w += q.w;
			return *this;
		}

		quaternion operator* (const float scalar) const {
			return quaternion(v*scalar, w*scalar);
		}

		quaternion& operator*= (const float scalar) {
			v *= scalar;
			w *= scalar;
			return *this;
		}

		float length() const {
			return std::sqrt(std::powf(w, 2) + std::powf(v.magnitude(), 2));
		}

		quaternion normalize() const {
			const float l = length();
			assert(l != 0.0f);
			return (*this)*(1.0f / l);
		}

		quaternion inverse() const {
			const float l = length();
			assert(l != 0.0f);
			const float f = 1.0f / std::pow(l, 2);
			return quaternion((-v)*f, w*f);
		}

		quaternion operator*(const quaternion& q) {
			return quaternion(
				w*q.v + q.w*v + v.cross(q.v),
				w*q.w - (v*q.v)
			);
		}

		quaternion& operator= (const quaternion& q) {
			// check for self-assignment 
			if (this == &q)
				return *this;

			// copy 
			v = q.v;
			w = q.w;
			return *this;
		}

		bool operator== (const quaternion& q) const {
			return v == q.v && w == q.w;
		}

		bool operator!= (const quaternion& q) const {
			return !(*this == q);
		}

		matrix4 matrix() const {
			const float xy = v.x*v.y;
			const float xz = v.x*v.z;
			const float yz = v.y*v.z;
			const float x2 = v.x*v.x;
			const float y2 = v.y*v.y;
			const float z2 = v.z*v.z;

			matrix4 m({
				1.0f-2*y2-2*z2,		2*xy+2*w*v.z,	2*xz-2*w*v.y,	0,
				2*xy-2*w*v.z,		1-2*x2-2*z2,	2*yz+2*w*v.z,	0,
				2*xz+2*w*v.y,		2*yz-2*w*v.x,	1-2*x2-2*y2,	0,
				0,					0,				0,				1
			});
			return m;
		}

		vector4 axisAngle() const {
			vector4 result;
			const float angle = 2.0f * std::acos(w);
			const float length = sqrt(1.0f - angle * angle);
			const float f = 1.0f / length;
			result.x *= f;
			result.y *= f;
			result.z *= f;
			result.w = angle;
			return result;
		}
	};

	quaternion operator* (const float scalar, const quaternion& q) {
		return q * scalar;
	}
};