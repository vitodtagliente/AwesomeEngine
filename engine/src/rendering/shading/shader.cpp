#include <awesome/rendering/shading/shader.h>
#include <awesome/rendering/context.h>
#include <awesome/utility/log.h>
#include <fstream>

namespace Awesome
{
	bool Shader::load_file(std::string filename, std::string& source)
	{
		std::string line{};
		source.clear();
		std::ifstream file(filename);
		auto log = Log::instance();
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
		if (status == ShaderStatus::Compiled)
			free();
	}

	bool Shader::compile(std::string filename)
	{
		if (type == ShaderType::VertexShader)
			id = glCreateShader(GL_VERTEX_SHADER);
		else if (type == ShaderType::FragmentShader)
			id = glCreateShader(GL_FRAGMENT_SHADER);
		else if(type == ShaderType::GeometryShader)
			id = glCreateShader(GL_GEOMETRY_SHADER);

		status = ShaderStatus::Error;

		std::string source{};
		if (load_file(filename, source) == false)
			return false;

		const char * sourcePointer = source.c_str();
		glShaderSource(id, 1, &sourcePointer, NULL);
		glCompileShader(id);
			
		int compile_status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
		if (!compile_status)
		{
			char log[1024];
			glGetShaderInfoLog(id, 1024, NULL, log);
			std::string error_message{ log };
			Log::instance()->log("Shader", error_message);
			return false;
		}
		Log::instance()->log("Shader", "compiled!");

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