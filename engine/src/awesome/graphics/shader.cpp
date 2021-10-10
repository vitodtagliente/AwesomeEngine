#include "shader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>

namespace graphics
{
	bool Shader::Reader::load(const std::string& filename, std::string& source)
	{
		std::string line{};
		source.clear();
		std::ifstream file;
		file.open(filename.c_str(), std::ifstream::in);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				source += line + "\n";
			}
			file.close();
			return true;
		}
		return false;
	}

	bool Shader::Reader::parse(const std::string& content, std::map<Type, std::string>& sources)
	{
		/*
		std::string line{};
		sources.clear();
		std::ifstream file;
		file.open(filename.c_str(), std::ifstream::in);
		if (file.is_open())
		{
			Type currenshader_type;
			bool firsfound{ false };
			std::string source{};
			while (std::getline(file, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (firsfound)
					{
						sources[currenshader_type] = source;
					}
					else firsfound = true;

					if (line.find("vertex") != std::string::npos)
						currenshader_type = Type::Vertex;
					else if (line.find("fragment") != std::string::npos)
						currenshader_type = Type::Fragment;

					source.clear();
				}
				else source += line + "\n";
			}

			if (firsfound && !source.empty())
			{
				sources[currenshader_type] = source;
			}

			file.close();
			return true;
		}
		return false;
		*/

		std::string line{};
		sources.clear();
		std::istringstream stream(content);
		if (!std::empty(content))
		{
			Type currenshader_type;
			bool firsfound{ false };
			std::string source{};
			while (std::getline(stream, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (firsfound)
					{
						sources[currenshader_type] = source;
					}
					else firsfound = true;

					if (line.find("vertex") != std::string::npos)
						currenshader_type = Type::Vertex;
					else if (line.find("fragment") != std::string::npos)
						currenshader_type = Type::Fragment;

					source.clear();
				}
				else source += line + "\n";
			}

			if (firsfound && !source.empty())
			{
				sources[currenshader_type] = source;
			}
			return true;
		}
		return false;
	}

	Shader::Shader(const Type type, const std::string& source)
		: m_id()
		, m_type(type)
		, m_state(State::Unknown)
		, m_errorMessage()
	{
		m_id = glCreateShader(type == Type::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		const char* source_pointer = source.c_str();
		glShaderSource(m_id, 1, &source_pointer, NULL);
		glCompileShader(m_id);

		int compile_state{};
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &compile_state);
		if (compile_state != GL_TRUE)
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
		free();
	}

	void Shader::free()
	{
		glDeleteShader(m_id);
		m_state = State::Unloaded;
	}
}