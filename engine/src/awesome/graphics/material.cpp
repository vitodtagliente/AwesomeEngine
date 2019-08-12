#include "material.h"

#include "shader_program.h"
#include "texture.h"

namespace awesome
{
	Material::Material(const Type t_type /*= Type::Default*/)
		: m_type(t_type)
		, m_shaderProgram()
		, m_properties()
		, m_instances()
		, m_parent()
	{

	}

	Material::Material(ShaderProgram * const t_shaderProgram, const Type t_type /*= Type::Default*/)
		: m_type(t_type)
		, m_shaderProgram(t_shaderProgram)
		, m_properties()
		, m_instances()
		, m_parent()
	{

	}

	Material::~Material()
	{
		for (Material* const instance : m_instances)
		{
			delete instance;
		}
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
			else if (pair.second.type == MaterialProperty::Type::Vec4)
			{
				const vec4& vec = std::get<vector4>(pair.second.value);
				m_shaderProgram->set(pair.first, vec.x, vec.y, vec.z, vec.w);
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

	Material* const Material::createInstance() const
	{
		Material* const new_instance = new Material(m_shaderProgram, m_type);
		new_instance->m_properties = m_properties;
		if (!isInstance())
		{
			m_instances.push_back(new_instance);
			new_instance->m_parent = const_cast<Material*>(this);
		}
		else
		{
			new_instance->m_parent = m_parent;
		}
		return new_instance;
	}
}