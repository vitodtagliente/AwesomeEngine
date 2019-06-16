#include "material_library.h"

#include "material.h"
#include "shader.h"
#include "shader_program.h"

namespace awesome
{
	const std::string MaterialLibrary::DefaultSpriteMaterialName{ "default_sprite_material" };

	MaterialLibrary::MaterialLibrary()
		: m_materials()
		, m_shaders()
		, m_programs()
	{
		generateDefaultMaterials();
	}

	MaterialLibrary::~MaterialLibrary()
	{
	}

	void MaterialLibrary::clear()
	{
		
	}

	Material* const MaterialLibrary::getMaterial(const std::string t_name) const
	{
		const auto it = m_materials.find(t_name);
		if (it != m_materials.end())
		{
			return it->second;
		}
		return nullptr;
	}

	Shader* const MaterialLibrary::getShader(const std::string& t_name) const
	{
		const auto it = m_shaders.find(t_name);
		if (it != m_shaders.end())
		{
			return it->second;
		}
		return nullptr;
	}

	ShaderProgram* const MaterialLibrary::getShaderProgram(const std::string& t_name) const
	{
		const auto it = m_programs.find(t_name);
		if (it != m_programs.end())
		{
			return it->second;
		}
		return nullptr;
	}

	void MaterialLibrary::generateDefaultMaterials()
	{
		const std::string sprite_vertex_source = R"(
			#version 330 core

			layout(location = 0) in vec4 position;
			layout(location = 1) in vec2 texCoord;

			out vec2 v_TexCoord;

			uniform mat4 u_MVP;

			void main()
			{
				gl_Position = u_MVP * position;
				v_TexCoord = texCoord;
			}
		)";

		const std::string sprite_fragment_source = R"(
			#version 330 core

			out vec4 fragColor;

			uniform vec4 u_Color;
			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main()
			{
				vec4 texColor = texture(u_Texture, v_TexCoord);
				fragColor = texColor;
			}
		)";
	}

}