#pragma once

#include "vector3.h"
#include "quaternion.h"

namespace awesome
{
	class transform
	{
	public:

		vector3 position;
		quaternion rotation;
		vector3 scale;

		transform()
			: position()
			, rotation()
			, scale(1.0f, 1.0f, 1.0f)
			, m_matrix(matrix4::identity)
		{

		}

		transform(const vector3& t_position, const quaternion& t_rotation, const vector3& t_scale)
			: position(t_position)
			, rotation(t_rotation)
			, scale(t_scale)
			, m_matrix(matrix4::identity)
		{

		}

		const matrix4& matrix() const { return m_matrix; }

		inline void update()
		{
			//m_matrix = matrix4::scale(scale) * rotation.matrix() * matrix4::translate(position);
			m_matrix = matrix4::scale(scale) * matrix4::rotate_z(rotation.z) * matrix4::translate(position);
		}

	private:

		// cached matrix
		matrix4 m_matrix;
	};
}