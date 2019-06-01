#pragma once

#include "../core/singleton.h"
#include "../data/color.h"
#include "../math/matrix4.h"
#include "command_buffer.h"

namespace awesome
{
	struct Mesh;
	class Renderable;
	class Material;
	class GraphicsModule;

	class Renderer : public Singleton<Renderer>
	{
	public:

		// dependency injection
		Renderer(GraphicsModule * const t_graphicsModule);
		virtual ~Renderer();

		virtual void enableAlpha(const bool bEnabled = true) = 0;
		virtual void clear(const Color& t_color) = 0;
		virtual void draw(const unsigned int t_vertices = 3) = 0;
		virtual void drawIndexed(const unsigned int t_vertices) = 0;
		
		void push(const Mesh& t_mesh);
		void push(Renderable* const t_renderable, Material* const t_material, const matrix4& t_transform = matrix4::identity);
		// render all pushed commands
		void render();

	protected:

		// graphics api
		GraphicsModule* m_graphicsModule;
		// command buffer
		CommandBuffer m_commandBuffer;
	};
}