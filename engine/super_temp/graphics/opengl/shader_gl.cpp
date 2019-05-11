#include "shader_gl.h"

#include "opengl.h"

namespace awesome
{
	ShaderGL::ShaderGL(const Type t_type, const std::string& t_source)
		: Shader(t_type, t_source)
	{
		m_id = glCreateShader(t_type == Type::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		const char* source_pointer = t_source.c_str();
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

	ShaderGL::~ShaderGL()
	{
		glDeleteShader(m_id);
		m_state = State::Unloaded;
	}
}
