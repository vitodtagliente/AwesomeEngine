#pragma once

#include <string>
#include <vector>
#include <map>
#include <variant>
#include <awesome/math/vector.h>
#include <awesome/math/matrix.h>

namespace awesome
{
	class ShaderProgram;
	class Texture;

	struct MaterialProperty
	{
		using value_t = std::variant<
			bool, float, int, 
			vec2, vec3, vec4, 
			mat2, mat3, mat4, 
			Texture*
		>;

		enum class Type
		{
			Bool,
			Float,
			Int,
			Texture1D,
			Texture2D,
			Texture3D,
			TextureCube,
			Vec2,
			Vec3,
			Vec4,
			Mat2,
			Mat3,
			Mat4
		};

		Type type;
		value_t value;
	};

	class Material
	{
	public:

		enum class Type
		{
			Default
		};

		Material(const Type t_type = Type::Default);
		Material(ShaderProgram * const t_shaderProgram, const Type t_type = Type::Default);
		Material(const Material& t_materal);
		~Material();

		void bind();
		void unbind();

		inline ShaderProgram * const getShaderProgram() const { return m_shaderProgram; }

		inline const std::map<std::string, MaterialProperty>& getProperties() const { return m_properties; }
		std::vector<MaterialProperty> getProperties(const MaterialProperty::Type t_type) const;

		void set(const std::string& t_name, const bool t_value);
		void set(const std::string& t_name, const int t_value);
		void set(const std::string& t_name, const float t_value);
		void set(const std::string& t_name, const vec2 t_value);
		void set(const std::string& t_name, const vec3 t_value);
		void set(const std::string& t_name, const vec4 t_value);
		void set(const std::string& t_name, const mat2 t_value);
		void set(const std::string& t_name, const mat3 t_value);
		void set(const std::string& t_name, const mat4 t_value);
		void set(const std::string& t_name, Texture * const t_value);

		struct params
		{
			params() = delete;

			static const std::string ModelViewProjectionMatrix;
			static const std::string Texture;
			static const std::string Color;
		};

	private:

		// material type
		Type m_type;
		// shader program
		ShaderProgram* m_shaderProgram;
		// material attributes
		std::map<std::string, MaterialProperty> m_properties;

	};
}