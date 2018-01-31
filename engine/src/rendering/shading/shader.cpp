#include <awesome/rendering/shading/shader.h>
#include <fstream>
#include <glad/glad.h>
#include <awesome/utility/log.h>

namespace Awesome
{
	namespace Rendering
	{

		bool Shader::load_file(std::string filename, std::string& source)
		{
			std::string line{};
			source.clear();
			std::ifstream file(filename);
			auto log = Utility::Log::instance();
			log->log("Shader", "loading file " + filename + "...");
			if (file.is_open())
			{
				while (std::getline(file, line)) {
					log->log(line);
					source += line + "\n";
				}
				file.close();
				return true;
			}
			log->log("Shader", "cannot find the shader source file");
			return false;
		}

		Shader::Shader(ShaderType shader_type)
		{
			type = shader_type;
		}
		
		Shader::~Shader()
		{
			if (status == Compiled)
				free();
		}

		bool Shader::compile(std::string filename)
		{
			id = glCreateShader(type);
			status = ShaderStatus::Error;

			std::string source{};
			if (load_file(filename, source) == false)
				return false;

			const char * sourcePointer = source.c_str();
			glShaderSource(id, 1, &sourcePointer, NULL);
			glCompileShader(id);
			
			int status;
			glGetShaderiv(id, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				char log[1024];
				glGetShaderInfoLog(id, 1024, NULL, log);
				std::string error_message{ log };
				Utility::Log::instance()->log("Shader", error_message);
				return false;
			}
			Utility::Log::instance()->log("Shader", "compiled!");

			status = ShaderStatus::Compiled;
			return true;
		}

		void Shader::free()
		{
			glDeleteShader(id); 
			status = ShaderStatus::Error;
		}

		Shader* Shader::load(std::string filename, ShaderType type)
		{
			auto shader = new Shader(type);
			shader->compile(filename);
			return shader;
		}

	}
}