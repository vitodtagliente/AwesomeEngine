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
			// material stuff
			if (Material * const material = command.material)
			{
				if (ShaderProgram * const program = material->getShaderProgram())
				{
					program->bind();
					program->set(Material::params::ModelViewProjectionMatrix, &command.transform.data[0]);

					const std::vector<MaterialProperty>& textures = material->getProperties(MaterialProperty::Type::Texture2D);
					for (int i = 0; i < textures.size(); ++i)
					{
						const MaterialProperty& property = textures[i];
						Texture* const texture = std::get<Texture*>(property.value);
						if (texture)
						{
							texture->bind();
							program->set(Material::params::Texture, i);
						}
					}

					// #todo color
					program->set(Material::params::Color, 1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
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
		push(m_quad, m_materialLibrary->get(Material::defaults::Sprite), t_transform);
	}

	void Renderer::drawRectangle(const vec2& t_position, const Color& t_color, const vec2& t_scale)
	{
		static Renderable* const quad_renderable = Renderer::instance()->getAPI()->createRenderable(Quad{});

		Material* const material = m_materialLibrary->get(Material::defaults::Solid);
		mat4 matrix = mat4::scale({ t_scale.x, t_scale.y, 0.0f })
			* mat4::translate({ t_position.x, t_position.y, 0.0f });
		push(quad_renderable, material, matrix);
	}
}