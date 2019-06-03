#include "renderer.h"

#include "graphics_module.h"
#include "render_command.h"
#include "shader_program.h"
#include "material.h"
#include "texture.h"

namespace awesome
{
	Renderer::Renderer(GraphicsModule * const t_graphicsModule)
		: m_graphicsModule(t_graphicsModule)
		, m_commandBuffer()
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
					program->set("u_MVP", &command.transform.data[0]);

					const std::vector<MaterialProperty>& textures = material->getProperties(MaterialProperty::Type::Texture2D);
					for (int i = 0; i < textures.size(); ++i)
					{
						const MaterialProperty& property = textures[i];
						Texture* const texture = std::get<Texture*>(property.value);
						if (texture)
						{
							texture->bind();
							program->set("u_Texture", i);
						}
					}
				}
			}
			// bind the data to render
			command.renderable->bind();
			// render the command
			drawIndexed(command.renderable->getMesh().indices.size());
		}

		m_commandBuffer.clear();
	}
}