#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include "../core/types.h"

namespace awesome
{
	class Shader;

	class ShaderProgram

	{
	public:

		enum class State
		{
			Unknown,
			Error,
			Linked
		};

		ShaderProgram(const std::initializer_list<Shader*>& t_shaders);

		virtual void bind() = 0;
		virtual void unbind() = 0;

		inline unsigned int id() const { return m_id; }
		inline State getState() const { return m_state; }
		inline const std::string& getErrorMessage() const { return m_errorMessage; }
		inline bool isValid() const { return m_id != 0; }

		// uniform setters
		virtual void set(const std::string& t_name, const bool t_value) = 0;
		virtual void set(const std::string& t_name, const int t_value) = 0;
		virtual void set(const std::string& t_name, const float t_value) = 0;
		virtual void set(const std::string& t_name, const float* const t_matrix) = 0;
		virtual void set(const std::string& t_name, const float t_f1, const float t_f2, const float t_f3, const float t_f4) = 0;

	protected:

		// program id
		unsigned int m_id;
		// state
		State m_state;
		// error message
		std::string m_errorMessage;
	};
}