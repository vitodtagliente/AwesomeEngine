#pragma once

#include <string>
#include <vector>
#include <map>
#include "../math/vector.h"

namespace awesome
{
	class ShaderProgram;

	struct MaterialAttribute
	{
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
		// variant value
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

		inline ShaderProgram * const getShaderProgram() const { return m_shaderProgram; }

		// material color
		vec4 color;

		inline const std::map<std::string, MaterialAttribute>& getAttributes() const { return m_attributes; }

	private:

		// material type
		Type m_type;
		// shader program
		ShaderProgram* m_shaderProgram;
		// material attributes
		std::map<std::string, MaterialAttribute> m_attributes;

	};
}