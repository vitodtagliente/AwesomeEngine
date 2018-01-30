#include <dreamkeeper/shading/program.h>
#include <glad/glad.h>
#include <dreamkeeper/utility/log.h>

using namespace Dreamkeeper::Utility;

namespace Dreamkeeper
{
	namespace Shading
	{

		Program::Program()
		{

		}

		Program::Program(std::initializer_list<Shader*> args)
		{
			linkShaders(args);
		}

		Program::~Program()
		{
			if (isCompiled())
				free();
		}

		void Program::linkShader(Shader* shader)
		{
			if (shader->isCompiled() == false) {
				return;
			}

			if (shader->isVertexShader())
				vs = shader;
			else if (shader->isFragmentShader())
				fs = shader;
			else if (shader->isGeometryShader())
				gs = shader;
		}

		void Program::linkShaders(std::initializer_list<Shader*> shaders)
		{
			for (auto begin = shaders.begin(); begin != shaders.end(); ++begin) {
				linkShader(*begin);
			}
		}

		bool Program::compile()
		{
			id = glCreateProgram();

			if (vs != nullptr) glAttachShader(id, vs->id);
			if (fs != nullptr) glAttachShader(id, fs->id);
			if (gs != nullptr) glAttachShader(id, gs->id);

			glLinkProgram(id);
			
			int status;
			glGetShaderiv(id, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				char log[1024];
				glGetShaderInfoLog(id, 1024, NULL, log);
				std::string error_message{ log };
				Log::instance()->log("ShaderProgram", error_message);

				glDeleteProgram(id);
				return false;
			}

			Log::instance()->log("ShaderProgram", "ready!");

			if (vs != nullptr) glDetachShader(id, vs->id);
			if (fs != nullptr) glDetachShader(id, fs->id);
			if (gs != nullptr) glDetachShader(id, gs->id);

			compiled = true;
			return true;
		}
		
		void Program::use()
		{
			if (!compiled) {
				if (!compile())
					return;
			}

			glUseProgram(id);
		}

		void Program::free(bool free_shaders_too /*= false*/)
		{
			glDeleteProgram(id);
			compiled = false;

			if (free_shaders_too) {
				if (vs != nullptr) vs->free();
				if (fs != nullptr) fs->free();
				if (gs != nullptr) gs->free();
			}
		}

		int Program::getUniformLocation(const char* name)
		{
			return glGetUniformLocation(id, name);
		}

		void Program::setBool(const char* name, bool value)
		{
			glUniform1i(getUniformLocation(name), (int)value);
		}

		void Program::setBool(int location, bool value)
		{
			glUniform1i(location, (int)value);
		}

		void Program::setInt(const char* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Program::setInt(int location, int value)
		{
			glUniform1i(location, value);
		}

		void Program::setFloat(const char* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Program::setFloat(int location, float value)
		{
			glUniform1f(location, value);
		}

	}
}