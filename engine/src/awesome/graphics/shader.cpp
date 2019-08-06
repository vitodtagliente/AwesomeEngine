#include "shader.h"

#include <fstream>
#include <sstream>

namespace awesome
{
	bool Shader::Reader::load(const std::string& t_filename, std::string& t_source)
	{
		std::string line{};
		t_source.clear();
		std::ifstream file;
		file.open(t_filename.c_str(), std::ifstream::in);
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

	bool Shader::Reader::parse(const std::string& t_content, std::map<Type, std::string>& t_sources)
	{
		/*
		std::string line{};
		t_sources.clear();
		std::ifstream file;
		file.open(t_filename.c_str(), std::ifstream::in);
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
		*/

		std::string line{};
		t_sources.clear();
		std::istringstream stream(t_content);
		if (!std::empty(t_content))
		{
			Type current_shader_type;
			bool first_found{ false };
			std::string source{};
			while (std::getline(stream, line))
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
			return true;
		}
		return false;
	}

	Shader::Shader(const Type t_type, const std::string & t_source)
		: m_id()
		, m_type(t_type)
		, m_state(State::Unknown)
		, m_errorMessage()
	{
	}
}