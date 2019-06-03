#include "material.h"

#include "shader_program.h"

namespace awesome
{
	Material::Material(const Type t_type /*= Type::Default*/)
		: m_type(t_type)
		, m_shaderProgram()
		, m_properties()
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

	std::vector<MaterialProperty> Material::getProperties(const MaterialProperty::Type t_type) const
	{
		std::vector<MaterialProperty> result;

		for (const auto& pair : m_properties)
		{
			if (pair.second.type == t_type)
			{
				result.push_back(pair.second);
			}
		}

		return std::move(result);
	}

	void Material::set(const std::string& t_name, const bool t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Bool, t_value} });
	}

	void Material::set(const std::string& t_name, const int t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Int, t_value} });
	}

	void Material::set(const std::string& t_name, const float t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Float, t_value} });
	}

	void Material::set(const std::string& t_name, const vec2 t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Vec2, t_value} });
	}

	void Material::set(const std::string& t_name, const vec3 t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Vec3, t_value} });
	}

	void Material::set(const std::string& t_name, const vec4 t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Vec4, t_value} });
	}

	void Material::set(const std::string& t_name, const mat2 t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Mat2, t_value} });
	}

	void Material::set(const std::string& t_name, const mat3 t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Mat3, t_value} });
	}

	void Material::set(const std::string& t_name, const mat4 t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Mat4, t_value} });
	}

	void Material::set(const std::string& t_name, Texture* const t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Texture2D, t_value} });
	}

}