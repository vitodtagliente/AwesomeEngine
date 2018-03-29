#include <awesome/rendering/shading/program.h>
#include <awesome/rendering/context.h>
#include <awesome/utility/log.h>
#include <cassert>

namespace Awesome
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
		if (status == ShaderStatus::Compiled)
			free();
	}

	void Program::linkShader(Shader* shader)
	{
		if (shader->getStatus() == ShaderStatus::Error) {
			return;
		}

		if (shader->getType() == ShaderType::VertexShader)
			vs = shader;
		else if (shader->getType() == ShaderType::FragmentShader)
			fs = shader;
		else if (shader->getType() == ShaderType::GeometryShader)
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
		status = ShaderStatus::Error;
			
		if (vs != nullptr) glAttachShader(id, vs->id);
		if (fs != nullptr) glAttachShader(id, fs->id);
		if (gs != nullptr) glAttachShader(id, gs->id);

		glLinkProgram(id);
			
		int compile_status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
		if (!compile_status)
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

		status = ShaderStatus::Compiled;
		return true;
	}
		
	void Program::use()
	{
		assert(status == ShaderStatus::Compiled);
		glUseProgram(id);
	}

	void Program::free(bool free_shaders_too /*= false*/)
	{
		glDeleteProgram(id);
		status = ShaderStatus::Error;

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

	void Program::setBool(const char* name, const bool value)
	{
		glUniform1i(getUniformLocation(name), (int)value);
	}

	void Program::setBool(const int location, const bool value)
	{
		glUniform1i(location, (int)value);
	}

	void Program::setInt(const char* name, const int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Program::setInt(const int location, const int value)
	{
		glUniform1i(location, value);
	}

	void Program::setFloat(const char* name, const float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Program::setFloat(const int location, const float value)
	{
		glUniform1f(location, value);
	}

	void Program::setVec3(const char* name, const glm::vec3& value)
	{
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}

	void Program::setVec3(const int location, const glm::vec3& value)
	{
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Program::setVec4(const char* name, const glm::vec4& value)
	{
		glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Program::setVec4(const int location, const glm::vec4& value)
	{
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Program::setMat4(const char* name, const glm::mat4& value)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Program::setMat4(const int location, const glm::mat4& value)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}