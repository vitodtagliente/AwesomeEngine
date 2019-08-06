#include "material_library.h"

#include <fstream>
#include "material.h"
#include "shader.h"
#include "shader_program.h"
#include "graphics_api.h"

namespace awesome
{
	MaterialLibrary::MaterialLibrary(GraphicsAPI* const t_api)
		: m_api(t_api)
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

	unsigned int MaterialLibrary::loadShaders(const std::string& t_path)
	{
		return 0;
	}
	
	bool MaterialLibrary::add(const std::string& t_name, Material* const t_material)
	{
		const auto it = m_materials.find(t_name);
		if (it == m_materials.end())
		{
			m_materials.insert({ t_name, t_material });
			return true;
		}
		return false;
	}
	
	bool MaterialLibrary::add(const std::string& t_name, Shader* const t_shader)
	{
		const auto it = m_shaders.find(t_name);
		if (it == m_shaders.end())
		{
			m_shaders.insert({ t_name, t_shader });
			return true;
		}
		return false;
	}
	
	bool MaterialLibrary::add(const std::string& t_name, ShaderProgram* const t_program)
	{
		const auto it = m_programs.find(t_name);
		if (it == m_programs.end())
		{
			m_programs.insert({ t_name, t_program });
			return true;
		}
		return false;
	}
	
	Material* const MaterialLibrary::get(const std::string& t_name) const
	{
		const auto it = m_materials.find(t_name);
		if (it != m_materials.end())
		{
			return it->second;
		}
		return nullptr;
	}
}