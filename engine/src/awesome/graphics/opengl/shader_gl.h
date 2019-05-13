#pragma once 

#include "../shader.h"

namespace awesome
{
	class ShaderGL final : public Shader
	{
	public:

		ShaderGL(const Type t_type, const std::string& t_source);
		~ShaderGL();
	};
}