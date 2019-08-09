#include "renderer.h"

#include "graphics_api.h"
#include "render_command.h"
#include "shader_program.h"
#include "material.h"
#include "material_library.h"
#include "texture.h"
#include "texture_library.h"
#include "mesh/mesh.h"
#include "mesh/quad.h"

namespace awesome
{
	Renderer::Renderer(GraphicsAPI* const t_api)
		: m_api(t_api)
		, m_commandBuffer()
		, m_materialLibrary(new MaterialLibrary(t_api))
		, m_textureLibrary(new TextureLibrary(t_api))
		, m_quad(t_api->createRenderable(Quad{}))
	{
	}
	
	Renderer::~Renderer()
	{
	}
	
	void Renderer::push(Renderable* const t_renderable, Material* const t_material, const matrix4& t_transform)
	{
		m_commandBuffer.push_back(RenderCommand(t_renderable, t_material, t_transform));
	}

	void Renderer::render()
	{
		for (const RenderCommand& command : m_commandBuffer.getCommands())
		{
			// bind the material
			command.material->bind();
			// bind the data to render
			command.renderable->bind();
			// render the command
			drawIndexed(command.renderable->getMesh().indices.size());
		}

		m_commandBuffer.clear();
	}
	
	void Renderer::drawTexture(Texture* const t_texture, const vector2& t_position)
	{
		drawTexture(
			t_texture, 
			matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawTexture(Texture* const t_texture, const vector2& t_position, const vector2& t_scale)
	{
		drawTexture(
			t_texture, 
			matrix4::scale(to_vec3(t_scale)) * matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawTexture(Texture* const t_texture, const vector2& t_position, const float t_theta)
	{
		drawTexture(
			t_texture,
			matrix4::rotate_z(t_theta) * matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawTexture(Texture* const t_texture, const vector2& t_position, const float t_theta, const vector2& t_scale)
	{
		drawTexture(
			t_texture,
			matrix4::scale(to_vec3(t_scale)) * matrix4::rotate_z(t_theta) * matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawTexture(Texture* const t_texture, const matrix4& t_transform)
	{
		Material* const spriteMaterial = m_materialLibrary->get(Material::defaults::Sprite)->createInstance();
		spriteMaterial->set(Material::params::ModelViewProjectionMatrix, t_transform);
		spriteMaterial->set(Material::params::Texture, t_texture);
		push(m_quad, spriteMaterial, t_transform);
	}

	void Renderer::drawRect(const Color& t_color, const vector2& t_position)
	{
		drawRect(
			t_color,
			matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawRect(const Color& t_color, const vector2& t_position, const vector2& t_scale)
	{
		drawRect(
			t_color,
			matrix4::scale(to_vec3(t_scale)) * matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawRect(const Color& t_color, const vector2& t_position, const float t_theta)
	{
		drawRect(
			t_color,
			matrix4::rotate_z(t_theta) * matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawRect(const Color& t_color, const vector2& t_position, const float t_theta, const vector2& t_scale)
	{
		drawRect(
			t_color,
			matrix4::scale(to_vec3(t_scale)) * matrix4::rotate_z(t_theta) * matrix4::translate(to_vec3(t_position))
		);
	}

	void Renderer::drawRect(const Color& t_color, const matrix4& t_transform)
	{
		Material* const solidMaterial = m_materialLibrary->get(Material::defaults::Solid)->createInstance();
		solidMaterial->set(Material::params::Color, t_color);
		solidMaterial->set(Material::params::ModelViewProjectionMatrix, t_transform);
		push(m_quad, solidMaterial, t_transform);
	}
}