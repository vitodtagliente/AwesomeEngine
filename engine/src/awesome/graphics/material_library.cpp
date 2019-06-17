#include "material_library.h"

#include <fstream>
#include "material.h"
#include "shader.h"
#include "shader_program.h"
#include "graphics_module.h"

namespace awesome
{
	MaterialLibrary::MaterialLibrary(GraphicsModule* const t_graphics)
		: m_graphics(t_graphics)
		, m_materials()
		, m_shaders()
		, m_programs()
	{

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

	unsigned int MaterialLibrary::loadMaterials(const std::string& t_path)
	{

		return 0;
	}
}