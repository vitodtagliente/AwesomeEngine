#pragma once

#include "mesh/mesh.h"

namespace awesome
{
	class Renderable
	{
	public:

		Renderable();
		Renderable(const Mesh& t_mesh);
		virtual ~Renderable();

		virtual void bind() = 0;
		virtual void unbind() = 0;

		inline const Mesh& getMesh() const { return m_mesh; }

	private:

		// mesh
		Mesh m_mesh;
	};
}