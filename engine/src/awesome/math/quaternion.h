#pragma once

#include <cmath>
#include "common.h"
#include "matrix.h"
#include "vector.h"

namespace awesome
{
	struct quaternion
	{
		// vector part
		vector3 v;

		// scalar part
		float w;

		quaternion();
		quaternion(const vector3& t_vector, const float t_scalar = 0.0f);
		quaternion(const float t_x, const float t_y, const float t_z, const float t_w = 0.0f);

		float length() const;

		quaternion normalize() const;
		quaternion inverse() const;

		// operator overloading

		quaternion operator- () const;
		quaternion operator+ (const quaternion& t_q) const;

		quaternion& operator+= (const quaternion& t_q);

		quaternion operator* (const float t_scalar) const;
		quaternion& operator*= (const float t_scalar);
		quaternion operator*(const quaternion& t_q) const ;

		quaternion& operator= (const quaternion& t_q);

		bool operator== (const quaternion& t_q) const;
		bool operator!= (const quaternion& t_q) const;

		matrix4 matrix() const;
		vector4 axisAngle() const;
	};

	quaternion operator* (const float t_scalar, const quaternion& t_q);
};