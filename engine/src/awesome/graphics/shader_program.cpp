#include "shader_program.h"
#include <glad/glad.h>

namespace awesome
{
	ShaderProgram::ShaderProgram(const std::initializer_list<Shader*>& t_shaders)
		: m_id()
		, m_state(State::Unknown)
		, m_uniformLocations()
		, m_errorMessage()
	{
		// create the program
		m_id = glCreateProgram();

		// attach shaders
		for (auto it = t_shaders.begin(); it != t_shaders.end(); ++it) 
		{
			auto shader = *it;
			if (shader)
			{
				glAttachShader(m_id, shader->getId());
			}
		}

		// link the program
		glLinkProgram(m_id);

		int compile_status;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &compile_status);
		if (!compile_status)
		{
			m_state = State::Error;
			// store the error message
			char log[1024];
			glGetShaderInfoLog(m_id, 1024, NULL, log);
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
					glDetachShader(m_id, shader->getId());
				}
			}
			m_state = State::Linked;
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::bind()
	{
		glUseProgram(m_id);
	}

	void ShaderProgram::unbind()
	{
		glUseProgram(0);
	}

	uint ShaderProgram::getId() const
	{
		return m_id;
	}

	ShaderProgram::State ShaderProgram::getState() const
	{
		return m_state;
	}

	const std::string& ShaderProgram::getErrorMessage() const
	{
		return m_errorMessage;
	}

	bool ShaderProgram::isValid() const
	{
		return m_state == State::Linked;
	}

	void ShaderProgram::set(const std::string& t_name, const bool t_value)
	{
		glUniform1i(getUniformLocation(t_name), static_cast<int>(t_value));
	}

	void ShaderProgram::set(const std::string& t_name, const int t_value)
	{
		glUniform1i(getUniformLocation(t_name), t_value);
	}

	void ShaderProgram::set(const std::string& t_name, const float t_value)
	{
		glUniform1f(getUniformLocation(t_name), t_value);
	}

	void ShaderProgram::set(const std::string& t_name, const float* const t_matrix)
	{
		glUniformMatrix4fv(getUniformLocation(t_name), 1, GL_FALSE, t_matrix);
	}

	void ShaderProgram::set(const std::string& t_name, const float t_f1, const float t_f2, const float t_f3, const float t_f4)
	{
		glUniform4f(getUniformLocation(t_name), t_f1, t_f2, t_f3, t_f4);
	}

	int ShaderProgram::getUniformLocation(const std::string& t_name)
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