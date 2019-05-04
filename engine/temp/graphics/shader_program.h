#pragma once

#include <map>
#include <string>
#include "shader.h"

namespace awesome
{
	class ShaderProgram final
	{
	public:

		enum class State
		{
			Unknown,
			Error,
			Linked
		};

		ShaderProgram(const std::initializer_list<Shader*>& t_shaders);
		~ShaderProgram();

		void bind();
		void unbind();

		uint getId() const;
		State getState() const;
		const std::string& getErrorMessage() const;
		bool isValid() const;

		// uniform setters
		void set(const std::string& t_name, const bool t_value);
		void set(const std::string& t_name, const int t_value);
		void set(const std::string& t_name, const float t_value);
		void set(const std::string& t_name, const float* const t_matrix);
		void set(const std::string& t_name, const float t_f1, const float t_f2, const float t_f3, const float t_f4);

	private:

		// find the uniform layout location
		int getUniformLocation(const std::string& t_name);

		// program id
		uint m_id;
		// state
		State m_state;
		// uniform locations
		std::map<std::string, uint> m_uniformLocations;
		// error message
		std::string m_errorMessage;
	};
}