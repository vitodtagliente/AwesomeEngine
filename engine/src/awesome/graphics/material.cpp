#include "material.h"

#include "shader_program.h"

namespace awesome
{
	Material::Material(const Type t_type /*= Type::Default*/)
		: m_type(t_type)
		, m_shaderProgram()
		, m_attributes()
	{

	}

	Material::Material(ShaderProgram * const t_shaderProgram, const Type t_type /*= Type::Default*/)
		: m_shaderProgram(t_shaderProgram)
		, m_type(t_type)
	{

	}

	Material::Material(const Material& t_materal)
	{
		m_type = t_materal.m_type;
		m_shaderProgram = t_materal.m_shaderProgram;
	}

	Material::~Material()
	{

	}

}