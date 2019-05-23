#pragma once
#pragma warning(disable : 4201)

#include <cassert>
#include <cmath>
#include "vector.h"
#include "matrix.h"

namespace awesome
{
	struct quaternion
	{
		union
		{
			struct
			{
				float x, y, z, w;
			};

			float data[4];
		};

		quaternion::quaternion()
			: x(), y(), z(), w(1.0f)
		{

		}

		quaternion::quaternion(const vector3& t_vector, const float t_scalar)
			: x(t_vector.x)
			, y(t_vector.y)
			, z(t_vector.z)
			, w(1.0f)
		{
		}

		quaternion::quaternion(const float t_x, const float t_y, const float t_z, const float t_w = 1.0f)
			: x(t_x)
			, y(t_y)
			, z(t_z)
			, w(t_w)
		{
		}

		float dot(const quaternion& t_quaternion) const
		{
			return (*this) * t_quaternion;
		}

		quaternion cross(const quaternion& t_quaternion) const
		{
			return quaternion(
				w * t_quaternion.x + x * t_quaternion.w + y * t_quaternion.z - z * t_quaternion.y,
				w * t_quaternion.y + y * t_quaternion.w + z * t_quaternion.x - x * t_quaternion.z,
				w * t_quaternion.z + z * t_quaternion.w + x * t_quaternion.y - y * t_quaternion.x,
				w * t_quaternion.w - x * t_quaternion.x + y * t_quaternion.y - z * t_quaternion.z
			);
		}

		matrix4 matrix() const 
		{
			const float xy = x * y;
			const float xz = x * z;
			const float yz = y * z;
			const float x2 = x * x;
			const float y2 = y * y;
			const float z2 = z * z;

			matrix4 result(
				1.0f - 2 * y2 - 2 * z2,		2 * xy + 2 * w * z,		2 * xz - 2 * w * y,		0.0f,
				2 * xy - 2 * w * z,			1 - 2 * x2 - 2 * z2,	2 * yz + 2 * w * z,		0.0f,
				2 * xz + 2 * w * y,			2 * yz - 2 * w * x,		1 - 2 * x2 - 2 * y2,	0.0f,
				0.0f,						0.0f,					0.0f,					1.0f
			);
			return result;
		}

		vector4 axisAngle() const 
		{
			vector4 result;
			const float angle = 2.0f * std::acos(w);
			const float l = sqrt(1.0f - angle * angle);
			assert(l != 0.0f);
			const float f = 1.0f / l;
			result.x *= f;
			result.y *= f;
			result.z *= f;
			result.w = angle;
			return result;
		}

		// operators overloading

		quaternion& operator= (const quaternion& t_quaternion)
		{
			// check for self-assignment
			if (this == &t_quaternion)
				return *this;

			// copy 
			x = t_quaternion.x;
			y = t_quaternion.y;
			z = t_quaternion.z;
			w = t_quaternion.w;
			return *this;
		}

		bool operator== (const quaternion& t_quaternion) const
		{
			return x == t_quaternion.x && y == t_quaternion.y
				&& z == t_quaternion.z && w == t_quaternion.w;
		}

		bool operator!= (const quaternion& t_quaternion) const
		{
			return x != t_quaternion.x || y != t_quaternion.y
				|| z != t_quaternion.z || w != t_quaternion.w;
		}

		quaternion operator- ()
		{
			return { -x, -y, -z, -w };
		}

		quaternion operator+ (const quaternion& t_quaternion) const
		{
			return {
				x + t_quaternion.x,
				y + t_quaternion.y,
				z + t_quaternion.z,
				w + t_quaternion.w
			};
		}

		quaternion& operator+= (const quaternion& t_quaternion)
		{
			x += t_quaternion.x;
			y += t_quaternion.y;
			z += t_quaternion.z;
			w += t_quaternion.w;
			return *this;
		}

		quaternion& operator-= (const quaternion& t_quaternion)
		{
			x -= t_quaternion.x;
			y -= t_quaternion.y;
			z -= t_quaternion.z;
			w -= t_quaternion.w;
			return *this;
		}

		quaternion operator* (const float t_scalar) const
		{
			return { x * t_scalar, y * t_scalar, z * t_scalar, w * t_scalar };
		}

		quaternion& operator*= (const float t_scalar)
		{
			x *= t_scalar;
			y *= t_scalar;
			z *= t_scalar;
			w *= t_scalar;
			return *this;
		}

		quaternion operator/ (const float t_scalar) const
		{
			assert(t_scalar != 0.0f);
			const float f = 1.0f / t_scalar;
			return { x * f, y * f, z * f, w * f };
		}

		quaternion& operator/= (const float t_scalar)
		{
			assert(t_scalar != 0.0f);
			const float f = 1.0f / t_scalar;
			x *= f;
			y *= f;
			z *= f;
			w *= f;
			return *this;
		}

		float length() const
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		quaternion normalize() const
		{
			const float l = length();
			assert(l != 0.0f);
			return (*this) * (1.0f / l);
		}

		quaternion inverse() const
		{
			const float l = length();
			assert(l != 0.0f);
			const float f = 1.0f / std::pow(l, 2);
			return quaternion(-x * f, -y * f, -z * f, w * f);
		}

		float operator* (const quaternion& t_quaternion) const
		{
			return w * t_quaternion.w + x * t_quaternion.x + y * t_quaternion.y + z * t_quaternion.z;
		}

		vector3 operator* (const vector3& t_vector) const
		{
			vector3 uv, uuv;
			vector3 qvec(x, y, z);
			uv = qvec.cross(t_vector);
			uuv = qvec.cross(uv);
			uv *= 2.0f * w;
			uuv *= 2.0f;

			return t_vector + uv + uuv;
		}

		vector4 operator* (const vector4& t_vector) const
		{
			vector3 vec(t_vector.x, t_vector.y, t_vector.z);
			vector3 uv, uuv;
			vector3 qvec(x, y, z);
			uv = qvec.cross(vec);
			uuv = qvec.cross(uv);
			uv *= 2.0f * w;
			uuv *= 2.0f;

			const vector3 sum = vec + uv + uuv;

			return vector4(sum.x, sum.y, sum.z, 1.0f);
		}
	};

	inline quaternion operator* (const float t_scalar, const quaternion& t_quaternion)
	{
		return t_quaternion * t_scalar;
	}
}