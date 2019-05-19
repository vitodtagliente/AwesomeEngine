#include "quaternion.h"

namespace awesome
{
	quaternion::quaternion()
		: v()
		, w()
	{
	}

	quaternion::quaternion(const vector3& t_vector, const float t_scalar) 
	{
		const float half_angle = 0.5f * radians(t_scalar);
		const float s = std::sin(half_angle);
		v.x = t_vector.x * s;
		v.y = t_vector.y * s;
		v.z = t_vector.z * s;
		w = std::cos(half_angle);
	}

	quaternion::quaternion(const float t_x, const float t_y, const float t_z, const float t_w) 
	{
		v.x = t_x;
		v.y = t_y;
		v.z = t_z;
		w = t_w;
	}

	float quaternion::length() const
	{
		return std::sqrt(std::powf(w, 2) + std::powf(v.magnitude(), 2));
	}

	quaternion quaternion::normalize() const 
	{
		const float l = length();
		assert(l != 0.0f);
		return (*this) * (1.0f / l);
	}

	quaternion quaternion::inverse() const 
	{
		const float l = length();
		assert(l != 0.0f);
		const float f = 1.0f / std::pow(l, 2);
		return quaternion((-v) * f, w * f);
	}

	quaternion quaternion::operator- () const
	{
		return quaternion(-v, -w);
	}

	quaternion quaternion::operator+ (const quaternion & t_q) const 
	{
		return quaternion(v + t_q.v, w + t_q.w);
	}

	quaternion& quaternion::operator+= (const quaternion & t_q) 
	{
		v += t_q.v;
		w += t_q.w;
		return *this;
	}

	quaternion quaternion::operator* (const float t_scalar) const 
	{
		return quaternion(v * t_scalar, w * t_scalar);
	}

	quaternion& quaternion::operator*= (const float t_scalar) 
	{
		v *= t_scalar;
		w *= t_scalar;
		return *this;
	}

	quaternion quaternion::operator*(const quaternion & t_q) const
	{
		return quaternion(
			w * t_q.v + t_q.w * v + v.cross(t_q.v),
			w * t_q.w - (v * t_q.v)
		);
	}

	quaternion& quaternion::operator= (const quaternion & t_q) 
	{
		// check for self-assignment 
		if (this == &t_q)
			return *this;

		// copy 
		v = t_q.v;
		w = t_q.w;
		return *this;
	}

	bool quaternion::operator== (const quaternion & t_q) const 
	{
		return v == t_q.v && w == t_q.w;
	}

	bool quaternion::operator!= (const quaternion & t_q) const 
	{
		return !(*this == t_q);
	}

	matrix4 quaternion::matrix() const 
	{
		const float xy = v.x * v.y;
		const float xz = v.x * v.z;
		const float yz = v.y * v.z;
		const float x2 = v.x * v.x;
		const float y2 = v.y * v.y;
		const float z2 = v.z * v.z;

		matrix4 m({
			1.0f - 2 * y2 - 2 * z2,		2 * xy + 2 * w * v.z,	2 * xz - 2 * w * v.y,	0,
			2 * xy - 2 * w * v.z,		1 - 2 * x2 - 2 * z2,	2 * yz + 2 * w * v.z,	0,
			2 * xz + 2 * w * v.y,		2 * yz - 2 * w * v.x,	1 - 2 * x2 - 2 * y2,	0,
			0,					0,				0,				1
			});
		return m;
	}

	vector4 quaternion::axisAngle() const 
	{
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

	quaternion operator* (const float t_scalar, const quaternion& t_q) 
	{
		return t_q * t_scalar;
	}
}