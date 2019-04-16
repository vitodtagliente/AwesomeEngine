#include "shader.h"

namespace awesome
{
	Shader::Shader(const Type t_type, const std::string& t_source)
		: m_id()
		, m_type(t_type)
		, m_state(State::Unknown)
		, m_errorMessage()
	{
	}

	Shader::~Shader()
	{
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
}