#pragma once

namespace awesome
{
	struct Mesh;

	class Renderable
	{
	public:

		Renderable();
		Renderable(const Mesh& t_mesh);
		virtual ~Renderable();

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}