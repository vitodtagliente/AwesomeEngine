#include "renderable.h"

#include "graphics_buffer.h"

namespace awesome
{
	Renderable::Renderable()
		: m_mesh()
	{
	}

	Renderable::Renderable(const Mesh& t_mesh)
		: m_mesh(t_mesh)
	{
	}

	Renderable::~Renderable()
	{
	}
}