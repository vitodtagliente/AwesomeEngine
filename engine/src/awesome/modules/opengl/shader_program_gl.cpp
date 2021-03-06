#include "shader_program_gl.h"

#include "opengl.h"
#include <awesome/graphics/shader.h>

namespace awesome
{
	ShaderProgramGL::ShaderProgramGL(const std::initializer_list<Shader*>& t_shaders)
		: ShaderProgram(t_shaders)
		, m_uniformLocations()
	{
		// create the program
		m_id = glCreateProgram();

		// attach shaders
		for (auto it = t_shaders.begin(); it != t_shaders.end(); ++it)
		{
			auto shader = *it;
			if (shader)
			{
				glAttachShader(m_id, shader->id());
			}
		}

		// link the program
		glLinkProgram(m_id);

		int link_status{};
		glGetProgramiv(m_id, GL_LINK_STATUS, &link_status);
		if (link_status != GL_TRUE)
		{
			m_state = State::Error;
			// store the error message
			char log[1024];
			glGetProgramInfoLog(m_id, 1024, NULL, log);
			m_errorMessage = std::string{ log };

			// delete the program
			glDeleteProgram(m_id);
		}
		else
		{
			// detach shaders
			for (auto it = t_shaders.begin(); it != t_shaders.end(); ++it)
			{
				auto shader = *it;
				if (shader)
				{
					glDetachShader(m_id, shader->id());
				}
			}
			m_state = State::Linked;
		}
	}

	ShaderProgramGL::~ShaderProgramGL()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgramGL::bind()
	{
		glUseProgram(m_id);
	}

	void ShaderProgramGL::unbind()
	{
		glUseProgram(0);
	}

	void ShaderProgramGL::set(const std::string& t_name, const bool t_value)
	{
		glUniform1i(getUniformLocation(t_name), static_cast<int>(t_value));
	}

	void ShaderProgramGL::set(const std::string& t_name, const int t_value)
	{
		glUniform1i(getUniformLocation(t_name), t_value);
	}

	void ShaderProgramGL::set(const std::string& t_name, const float t_value)
	{
		glUniform1f(getUniformLocation(t_name), t_value);
	}

	void ShaderProgramGL::set(const std::string& t_name, const float* const t_matrix)
	{
		glUniformMatrix4fv(getUniformLocation(t_name), 1, GL_FALSE, t_matrix);
	}

	void ShaderProgramGL::set(const std::string& t_name, const float t_f1, const float t_f2, const float t_f3, const float t_f4)
	{
		glUniform4f(getUniformLocation(t_name), t_f1, t_f2, t_f3, t_f4);
	}

	int ShaderProgramGL::getUniformLocation(const std::string& t_name) const
	{
		if (m_uniformLocations.find(t_name) != m_uniformLocations.end())
		{
			return m_uniformLocations[t_name];
		}

		int location = glGetUniformLocation(m_id, t_name.c_str());
		if (location >= 0)
		{
			m_uniformLocations[t_name] = location;
		}
		return location;
	}
}