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
	class MaterialLibrary;
	class TextureLibrary;

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
		virtual void setViewport(const int t_width, const int t_height) = 0;
		
		void push(Renderable* const t_renderable, Material* const t_material, const matrix4& t_transform = matrix4::identity);
		// render all pushed commands
		void render();

		inline MaterialLibrary* const getMaterialLibrary() const { return m_materialLibrary; }
		inline TextureLibrary* const getTextureLibrary() const { return m_textureLibrary; }

	protected:

		// graphics api
		GraphicsModule* m_graphicsModule;
		// command buffer
		CommandBuffer m_commandBuffer;
		// material library
		MaterialLibrary* m_materialLibrary;
		// texture library
		TextureLibrary* m_textureLibrary;
	};
}