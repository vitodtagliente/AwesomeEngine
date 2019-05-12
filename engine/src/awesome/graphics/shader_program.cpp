#include "shader_program.h"

namespace awesome
{
	ShaderProgram::ShaderProgram(const std::initializer_list<Shader*>& t_shaders)
		: m_id()
		, m_state(State::Unknown)
		, m_errorMessage()
	{
	}
}