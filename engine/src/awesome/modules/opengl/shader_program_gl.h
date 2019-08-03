#pragma once

#include <awesome/graphics/shader_program.h>

namespace awesome
{
	class ShaderProgramGL final : public ShaderProgram
	{
	public:

		ShaderProgramGL(const std::initializer_list<Shader*>& t_shaders);
		~ShaderProgramGL();

		virtual void bind() override;
		virtual void unbind() override;

		// uniform setters
		virtual void set(const std::string& t_name, const bool t_value) override;
		virtual void set(const std::string& t_name, const int t_value) override;
		virtual void set(const std::string& t_name, const float t_value) override;
		virtual void set(const std::string& t_name, const float* const t_matrix) override;
		virtual void set(const std::string& t_name, const float t_f1, const float t_f2, const float t_f3, const float t_f4) override;

	private:

		// find the uniform layout location
		int getUniformLocation(const std::string& t_name);

		// uniform locations
		std::map<std::string, unsigned int> m_uniformLocations;
	};
}