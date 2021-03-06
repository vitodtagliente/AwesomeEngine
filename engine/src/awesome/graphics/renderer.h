#pragma once

#include <awesome/core/singleton.h>
#include <awesome/core/color.h>
#include <awesome/math/vector.h>
#include <awesome/math/matrix.h>
#include <awesome/math/rectangle.h>
#include "command_buffer.h"

namespace awesome
{
	struct Mesh;
	class Renderable;
	class Material;
	class GraphicsAPI;
	class MaterialLibrary;
	class TextureLibrary;
	class Texture;

	class Renderer : public Singleton<Renderer>
	{
	public:

		enum class DrawingMode
		{
			Fill,
			Lines
		};

		// dependency injection
		Renderer(GraphicsAPI* const t_api);
		virtual ~Renderer();
		
		virtual void enableAlpha(const bool bEnabled = true) = 0;
		virtual void clear(const Color& t_color) = 0;
		virtual void draw(const unsigned int t_vertices = 3) = 0;
		virtual void drawIndexed(const unsigned int t_vertices) = 0;
		virtual void setViewport(const int t_width, const int t_height) = 0;
		virtual void setDrawingMode(const DrawingMode t_drawingMode);
		
		void push(Renderable* const t_renderable, Material* const t_material, const matrix4& t_transform = matrix4::identity);
		// render all pushed commands
		void render();

		inline GraphicsAPI* const getAPI() const { return m_api; }
		inline MaterialLibrary* const getMaterialLibrary() const { return m_materialLibrary; }
		inline TextureLibrary* const getTextureLibrary() const { return m_textureLibrary; }

		// basic 2d drawing utilites
		void drawTexture(Texture* const t_texture, const vector2& t_position);
		void drawTexture(Texture* const t_texture, const vector2& t_position, const vector2& t_scale);
		void drawTexture(Texture* const t_texture, const vector2& t_position, const float t_theta);
		void drawTexture(Texture* const t_texture, const vector2& t_position, const float t_theta, const vector2& t_scale);
		void drawTexture(Texture* const t_texture, const matrix4& t_transform);
		// draw texture atlas
		void drawTextureCrop(Texture* const t_texture, const rect& t_rect, const vector2& t_position);
		void drawTextureCrop(Texture* const t_texture, const rect& t_rect, const vector2& t_position, const vector2& t_scale);
		void drawTextureCrop(Texture* const t_texture, const rect& t_rect, const vector2& t_position, const float t_theta);
		void drawTextureCrop(Texture* const t_texture, const rect& t_rect, const vector2& t_position, const float t_theta, const vector2& t_scale);
		void drawTextureCrop(Texture* const t_texture, const rect& t_rect, const matrix4& t_transform);
		// draw a rectangle 
		void drawRect(const Color& t_color, const vector2& t_position);
		void drawRect(const Color& t_color, const vector2& t_position, const vector2& t_scale);
		void drawRect(const Color& t_color, const vector2& t_position, const float t_theta);
		void drawRect(const Color& t_color, const vector2& t_position, const float t_theta, const vector2& t_scale);
		void drawRect(const Color& t_color, const matrix4& t_transform);
		// draw circle
		void drawCircle(const Color& t_color, const vector2& t_position, const float t_radius);

	protected:

		// graphics api
		GraphicsAPI* m_api;
		// command buffer
		CommandBuffer m_commandBuffer;
		// material library
		MaterialLibrary* m_materialLibrary;
		// texture library
		TextureLibrary* m_textureLibrary;

		// renderable for sprites
		Renderable* m_quad;
		Renderable* m_circle;
		// drawing mode
		DrawingMode m_drawingMode;
	};
}