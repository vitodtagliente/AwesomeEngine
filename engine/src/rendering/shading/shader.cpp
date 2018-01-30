#include <awesome/rendering/shading/shader.h>
#include <fstream>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
	{

		bool Shader::load_file(std::string filename, std::string& source)
		{
			std::string line{};
			source.clear();
			std::ifstream file(filename);
			//Log::instance()->log("Shader", "loading file " + filename + "...");
			if (file.is_open())
			{
				while (std::getline(file, line)) {
					//Log::instance()->log(line);
					source += line + "\n";
				}
				file.close();
				return true;
			}
			//Log::instance()->log("Shader", "cannot find the shader source file");
			return false;
		}

		Shader::Shader(ShaderType shader_type)
		{
			type = shader_type;
		}

		Shader::Shader(ShaderType shader_type, std::string shader_name)
		{
			type = shader_type;
			name = shader_name;
		}

		Shader::~Shader()
		{
			if (compiled)
				free();
		}

		bool Shader::compile(std::string filename)
		{
			id = glCreateShader(type);

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
				Log::instance()->log("Shader", error_message);
				return false;
			}
			Log::instance()->log("Shader", "compiled!");

			compiled = true;
			return compiled;
		}

		void Shader::free()
		{
			glDeleteShader(id); 
			compiled = false;
		}

		Shader* Shader::load(std::string filename, ShaderType type)
		{
			auto shader = new Shader(type, filename);
			shader->compile(filename);
			return shader;
		}

	}
}