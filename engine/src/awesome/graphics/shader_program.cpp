#include "shader_program.h"

#include <glad/glad.h>
#include "shader.h"

ShaderProgram::ShaderProgram(const std::initializer_list<Shader*>& shaders)
	: m_id()
	, m_state(State::Unknown)
	, m_errorMessage()
	, m_uniformLocations()
{
	// create the program
	m_id = glCreateProgram();

	// attach shaders
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
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
		for (auto it = shaders.begin(); it != shaders.end(); ++it)
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

void ShaderProgram::set(const std::string& name, const bool value)
{
	glUniform1i(getUniformLocation(name), static_cast<int>(value));
}

void ShaderProgram::set(const std::string& name, const int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void ShaderProgram::set(const std::string& name, const float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void ShaderProgram::set(const std::string& name, float* const matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix);
}

void ShaderProgram::set(const std::string& name, const float f1, const float f2, const float f3, const float f4)
{
	glUniform4f(getUniformLocation(name), f1, f2, f3, f4);
}

int ShaderProgram::getUniformLocation(const std::string& name) const
{
	if (m_uniformLocations.find(name) != m_uniformLocations.end())
	{
		return m_uniformLocations[name];
	}

	int location = glGetUniformLocation(m_id, name.c_str());
	if (location >= 0)
	{
		m_uniformLocations[name] = location;
	}
	return location;
}