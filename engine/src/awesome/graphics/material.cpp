#include "material.h"

#include "shader_program.h"
#include "texture.h"

namespace awesome
{
	const std::string Material::params::Color = "u_Color";
	const std::string Material::params::ModelViewProjectionMatrix = "u_ModelViewProjectionMatrix";
	const std::string Material::params::Texture = "u_Texture";

	const std::string Material::defaults::Solid = "solid";
	const std::string Material::defaults::Sprite = "sprite";

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

	void Material::bind()
	{
		m_shaderProgram->bind();

		int textures_counter = 0;
		for (const auto& pair : m_properties)
		{
			if (pair.second.type == MaterialProperty::Type::Texture2D)
			{
				Texture* const texture = std::get<Texture*>(pair.second.value);
				if (texture)
				{
					texture->bind();
					m_shaderProgram->set(pair.first, textures_counter++);
				}
			}
			else if (pair.second.type == MaterialProperty::Type::Color)
			{
				const Color& color = std::get<Color>(pair.second.value);
				m_shaderProgram->set(pair.first, color.red, color.green, color.blue, color.alpha);
			}
			else if (pair.second.type == MaterialProperty::Type::Mat4)
			{
				const matrix4& matrix = std::get<matrix4>(pair.second.value);
				m_shaderProgram->set(pair.first, &matrix.data[0]);
			}
		}
	}

	void Material::unbind()
	{
		m_shaderProgram->unbind();
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

		return result;
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

	void Material::set(const std::string& t_name, const Color& t_value)
	{
		m_properties.insert({ t_name, {MaterialProperty::Type::Color, t_value} });
	}

}