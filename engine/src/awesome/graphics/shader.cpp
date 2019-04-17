#include "shader.h"
#include <glad/glad.h>
#include <fstream>

namespace awesome
{
	Shader::Shader(const Type t_type, const std::string& t_source)
		: m_id()
		, m_type(t_type)
		, m_state(State::Unknown)
		, m_errorMessage()
	{
		m_id = glCreateShader(t_type == Type::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		const char* source_pointer = t_source.c_str();
		glShaderSource(m_id, 1, &source_pointer, NULL);
		glCompileShader(m_id);

		int compile_state;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &compile_state);
		if (!compile_state)
		{
			m_state = State::Error;
			char log[1024];
			glGetShaderInfoLog(m_id, 1024, NULL, log);
			m_errorMessage = std::string{ log };
		}
		else m_state = State::Compiled;
	}

	Shader::~Shader()
	{
		glDeleteShader(m_id);
		m_state = State::Unloaded;
	}

	uint Shader::getId() const
	{
		return m_id;
	}

	Shader::Type Shader::getType() const
	{
		return m_type;
	}

	Shader::State Shader::getState() const
	{
		return m_state;
	}

	const std::string& Shader::getErrorMessage() const
	{
		return m_errorMessage;
	}

	bool Shader::isValid() const
	{
		return m_state == State::Compiled;
	}

	bool Shader::Reader::load(const std::string& t_filename, std::string& t_source)
	{
		std::string line{};
		t_source.clear();
		std::ifstream file(t_filename);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				t_source += line + "\n";
			}
			file.close();
			return true;
		}
		return false;
	}

	bool Shader::Reader::parse(const std::string& t_filename, std::map<Type, std::string>& t_sources)
	{
		std::string line{};
		t_sources.clear();
		std::ifstream file(t_filename);
		if (file.is_open())
		{
			Type current_shader_type;
			bool first_found{ false };
			std::string source{};
			while (std::getline(file, line)) 
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (first_found) 
					{
						t_sources[current_shader_type] = source;
					}
					else first_found = true;

					if (line.find("vertex") != std::string::npos)
						current_shader_type = Type::Vertex;
					else if (line.find("fragment") != std::string::npos)
						current_shader_type = Type::Fragment;

					source.clear();
				}
				else source += line + "\n";
			}

			if (first_found && !source.empty()) 
			{
				t_sources[current_shader_type] = source;
			}

			file.close();
			return true;
		}
		return false;
	}
}